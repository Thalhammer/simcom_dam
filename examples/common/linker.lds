PHDRS {
  LR_1 PT_LOAD;
}

MEMORY {
  ram (rwxai) : ORIGIN = 0x42000000, LENGTH = 3M
}

SECTIONS {
  ER_RO 0x42000000 : {
	Image$$ER_RO$$Base = .;
	*txm_module_preamble.gcc.S.o (Init)
	*txm_module_preamble.gcc.S.o (.text .text.*)
	*txm_module_preamble.gcc.S.o (.rodata .rodata.*)

  __preinit_array_start = .;
  KEEP(*(SORT(.preinit_array.*)));
  KEEP(*(.preinit_init_array*));
  __preinit_array_end = .;

	__init_array_start = .;
  KEEP( *(SORT(.init_array.*)) );
  KEEP( *(.init_array*) );
	__init_array_end = .;

  __fini_array_start = .;
  KEEP( *(SORT(.fini_array.*)) );
  KEEP( *(.fini_array*) );
  __fini_array_end = .;

	* (.text .text.* i.*)
  * (.glue_7t)
  * (.glue_7)
  * (.ctors)
  * (.dtors)
  * (.gnu.linkonce.t.*)
  * (.gnu.linkonce.r.*)
  * (.gcc_except_table)

  * (.ARM.extab* .gnu.linkonce.armextab.*)
  __exidx_start = .;
	* (.ARM.exidx* .gnu.linkonce.armexidx.*)
  __exidx_end = .;

	* (.rodata .rodata* .constdata* .conststring*)
  . = ALIGN(16);
  } > ram : LR_1


  ER_RW ALIGN(16) : {
	Image$$ER_RO$$Limit = .;
	Image$$ER_RW$$Base = .;
	KEEP(* (.data .data.*))
  . = ALIGN(16);
  } > ram : LR_1

  ER_ZI ALIGN(16) : {
	Image$$ER_RW$$Limit = .;
	Image$$ER_ZI$$Base = .;
   *(.bss* .bss.* .common COMMON)
  . = ALIGN(16);
	Image$$ER_ZI$$Limit = .;
  } > ram : LR_1

  Image$$ER_RW$$Length = Image$$ER_RW$$Limit - Image$$ER_RW$$Base;
  Image$$ER_RO$$Length = Image$$ER_RO$$Limit - Image$$ER_RO$$Base;
  Image$$ER_ZI$$ZI$$Length = Image$$ER_ZI$$Limit - Image$$ER_ZI$$Base;
  ASSERT((Image$$ER_RW$$Length + Image$$ER_RO$$Length + 0x42000000) == Image$$ER_RW$$Limit, "Linker detected size missmatch in RW section, check linker script")
  ASSERT((Image$$ER_ZI$$ZI$$Length + Image$$ER_RW$$Length + Image$$ER_RO$$Length + 0x42000000) == Image$$ER_ZI$$Limit, "Linker detected size missmatch in ZI section, check linker script")

  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
}