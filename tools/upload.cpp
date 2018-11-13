#include "qualcomm/qcdm_serial.h"
#include "qualcomm/dm_efs_manager.h"
#include <iostream>
#include <string>
#include <chrono>

using namespace OpenPST::QC;
using OpenPST::Serial::SerialError;
using namespace std::string_literals;

int main(int argc, char**argv) {

	if (argc < 3) {
		std::cout << "Usage: " << argv[0] << " [port] [local]" << std::endl;
		return -1;
	}

	bool use_update = false;
	for(int i = 3; i<argc; i++) {
		if(argv[i] == "--update"s) use_update = true;
	}

	try {
		std::string remote_path = "cust_app.bin";
		if(use_update) remote_path = "cust_app.update";

		QcdmSerial port(argv[1], 38400, 150);
		DmEfsManager mgr(port);
		mgr.setSubsystemId(kDiagSubsysEfsAlternate);

		mgr.hello();
		auto contents = mgr.readDir("/");
		auto cnt = std::count_if(contents.begin(), contents.end(), [](const DmEfsNode& e){
			return e.name == "custapp" && e.isDir();
		});
		if(cnt != 1) {
			std::cout << "Could not find custapp folder, creating it" << std::endl;
			mgr.mkdir("custapp", 0x41ff);
		}

		contents =  mgr.readDir("custapp");
		cnt = std::count_if(contents.begin(), contents.end(), [&remote_path](const DmEfsNode& e){
			return e.name == remote_path && e.isFile();
		});
		mgr.unlink("custapp/" + remote_path);

		{
			std::ifstream in(argv[2], std::ios::in | std::ios::binary);
			if (!in.is_open()) {
				std::cout << "local open failed" << std::endl;
				return -1;
			}
			std::vector<char> buffer((std::istreambuf_iterator<char>(in)), (std::istreambuf_iterator<char>()));

			auto fp = mgr.open("custapp/" + remote_path, O_WRONLY | O_CREAT, 0x000081b6);
			if (fp < 0) {
				std::cout << "open failed" << std::endl;
				return -1;
			}

			auto start = std::chrono::steady_clock::now();
			size_t written = 0;
			while(written != buffer.size()){
				written += mgr.write(fp, reinterpret_cast<uint8_t*>(buffer.data() + written), buffer.size() - written, written);
			}
			auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0;
			std::cout << "Uploaded " << written << " bytes in " << dur << "s (" << (written/dur) << " byte/s)" << std::endl;

			mgr.close(fp);
		}
		port.close();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}