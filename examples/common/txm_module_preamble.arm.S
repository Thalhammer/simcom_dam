    AREA  Init, CODE, READONLY
    CODE32
;    /* Define public symbols.  */

    EXPORT __txm_module_preamble


    ;    /* Define application-specific start/stop entry points for the module.  */

    IMPORT _libc_app_init


    ;    /* Define common external refrences.  */

    IMPORT  _txm_module_thread_shell_entry
    IMPORT  _txm_module_callback_request_thread_entry
    IMPORT  |Image$$ER_RO$$Length|
    #ifdef TX_DAM_QC_CUSTOMIZATIONS
    IMPORT  |Image$$ER_RW$$Length|
    IMPORT  |Image$$ER_ZI$$ZI$$Length|
    #endif


__txm_module_preamble
    DCD       0x4D4F4455                                        ; Module ID
    DCD       0x5                                               ; Module Major Version
    DCD       0x3                                               ; Module Minor Version
    DCD       32                                                ; Module Preamble Size in 32-bit words
    DCD       0x134350ac                                        ; Module ID (application defined) 
    DCD       0x01000000                                        ; Module Properties where:
    ;   Bits 31-24: Compiler ID
    ;           0 -> IAR
    ;           1 -> RVDS
    ;           2 -> GNU
    ;   Bits 23-0:  Reserved
    DCD       _txm_module_thread_shell_entry - . + .            ; Module Shell Entry Point
    DCD       _libc_app_init - . + .                        ; Module Start Thread Entry Point
    DCD       0                                                 ; Module Stop Thread Entry Point 
    DCD       140                                               ; Module Start/Stop Thread Priority
    DCD       8192                                              ; Module Start/Stop Thread Stack Size
    DCD       _txm_module_callback_request_thread_entry - . + . ; Module Callback Thread Entry
    DCD       25                                                ; Module Callback Thread Priority     
    DCD       2046                                              ; Module Callback Thread Stack Size    
    DCD       |Image$$ER_RO$$Length|                            ; Module Code Size
    #ifdef TX_DAM_QC_CUSTOMIZATIONS
    DCD       |Image$$ER_ZI$$ZI$$Length|                        ; Module data size - get it from ZI section
    DCD       __txm_module_preamble                             ; Reserved 0
    DCD       |Image$$ER_RW$$Length|                            ; Reserved 1
    #else
    DCD       0x16000                                            ; Module Data Size - default to 16K (need to make sure this is large enough for module's data needs!)
    DCD       0                                                 ; Reserved 0
    DCD       0                                                 ; Reserved 1
    #endif      
    DCD       0                                                 ; Reserved 2
    DCD       0                                                 ; Reserved 3
    DCD       0                                                 ; Reserved 4
    DCD       0                                                 ; Reserved 5     
    DCD       0                                                 ; Reserved 6     
    DCD       0                                                 ; Reserved 7   
    DCD       0                                                 ; Reserved 8  
    DCD       0                                                 ; Reserved 9
    DCD       0                                                 ; Reserved 10
    DCD       0                                                 ; Reserved 11
    DCD       0                                                 ; Reserved 12
    DCD       0                                                 ; Reserved 13
    DCD       0                                                 ; Reserved 14
    DCD       0                                                 ; Reserved 15

    END


