
ENTRY(Reset_Handler)

MEMORY{
	FLASH(rx): ORIGIN = 0x08000000, LENGTH = 0x0000FFFF
	SRAM(rwx): ORIGIN = 0x20000000, LENGTH = 8K
}

STACK_SIZE = 4k;

SECTIONS{
	
	/* Section for the vector table */
	.isr_vector :
	{
		*(.isr_vector)
		. = ALIGN(4);
	} >FLASH
	
	/* Section for the program code */
	.text :
	{
		*(.text)
		. = ALIGN(4);
		*(.text.*)
		. = ALIGN(4);
		_etext = .;
	} >FLASH
	
	/* Section for the read-only data. */
	/* Read-only data may as well be stored in flash memory to avoid copying it to RAM */
	.rodata :
	{
		*(.rodata)
		. = ALIGN(4);
		*(.rodata.*)
		. = ALIGN(4);
	} >FLASH
	

	.ARM.extab   :
	{
		. = ALIGN(4);
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		. = ALIGN(4);
	} >FLASH

	.ARM :
	{
		. = ALIGN(4);
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
		. = ALIGN(4);
	} >FLASH

	.preinit_array :
	{
		. = ALIGN(4);
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array*))
		PROVIDE_HIDDEN (__preinit_array_end = .);
		. = ALIGN(4);
	} >FLASH

	.init_array :
	{
		. = ALIGN(4);
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
		. = ALIGN(4);
	} >FLASH

	.fini_array :
	{
		. = ALIGN(4);
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array*))
		PROVIDE_HIDDEN (__fini_array_end = .);
		. = ALIGN(4);
	} >FLASH
	
	
	/* The stack */
	.stack :
	{
		_sstack = .;
		. = . + STACK_SIZE;
		. = ALIGN(4);
		_estack = .;
	} > SRAM
	
	/* Initialized data */
	/* Stored in flash memory but will be copied into RAM memory */
	.data :
	{
		_sdata_flash = LOADADDR(.data);
		_sdata_sram = .;
		*(.data)
		. = ALIGN(4);
		*(.data.*)
		. = ALIGN(4);
		_edata_flash = LOADADDR(.data) + SIZEOF(.data);
		_edata_sram = .;
	} >SRAM AT> FLASH
	
	/* Not initialized data. Set to 0 */
	.bss :
	{
		_sbss = .;
		*(.bss)
		. = ALIGN(4);
		*(.bss.*)
		. = ALIGN(4);
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	} >SRAM
	
	/* Similar to the .bss section but this data that will not be initialized to 0 during startup (Reset_Handler)*/
	/* This is to allow data to be saved between processor restarts when power is not lost */
	.no_init :
	{
		_sno_init = .;
		*(.no_init)
		. = ALIGN(4);
		*(.no_init.*)
		. = ALIGN(4);
		_eno_init = .;
	} >SRAM

	/* Remove information from the compiler libraries */
	/DISCARD/ :
	{
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	}

	.ARM.attributes 0 : { *(.ARM.attributes) }

}
