/* Linker script pour STM32F407 bare-metal */

ENTRY(Reset_Handler)

/* Définition de la mémoire */
MEMORY
{
  RAM    (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
  ROM    (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K
}

/* Pointeur de fin de stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Taille minimale heap et stack (modifiable si besoin) */
_Min_Heap_Size  = 0x200;
_Min_Stack_Size = 0x400;

SECTIONS
{
  /* Vecteurs d'interruption */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >ROM

  /* Code exécutable */
  .text :
  {
    . = ALIGN(4);
    *(.text*)          /* toutes les sections .text */
    *(.glue_7)
    *(.glue_7t)
    KEEP(*(.init))
    KEEP(*(.fini))
    . = ALIGN(4);
  } >ROM

  /* Données constantes */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
  } >ROM

  /* Données initialisées */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;          /* début des données initialisées */
    *(.data*)
    _edata = .;          /* fin des données initialisées */
  } >RAM AT>ROM

  /* Section bss (non initialisée) */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;           /* début bss */
    __bss_start__ = _sbss;
    *(.bss*)
    *(COMMON)
    _ebss = .;           /* fin bss */
    __bss_end__ = _ebss;
    . = ALIGN(4);
  } >RAM

  /* Heap et stack utilisateur */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE(end = .);
    PROVIDE(_end = .);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* Supprimer les objets libc/libm si Newlib est utilisé */
  /DISCARD/ :
  {
    libc.a(*)
    libm.a(*)
    libgcc.a(*)
  }
}
