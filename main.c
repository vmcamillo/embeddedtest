#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Test Description
 * -----------------
 * You have to write a write data routine for a UART device. The UART is a memmory
 * mapped device at the address 0xFC000000 on an embedded platform.
 * To access the memory, use the functions stub_memwrite. This 
 * functions bypass the operating system and access the memory of the device.
 * This peripheral is controlled by the following 32 bit registers (offsets given)
 
 * BRR: Baud rate register Offset: 0x4 
 * - Selects the baud rate and configure UART device
 *
 * TER: Transmit enable register Offset: 0x8
 *  - Bit 23 in this register enables the transmit operation. When bit 23 is set to 1, 
 *    data in TDR[0:8] is sent via UART. Imediately After that, bit 23 is automatically set to 0.
 *
 * RER: Receive  enabel register Offset: 0xC
 * - Bits 3 and 5 notify overrun and framing error and need to be cleared upon reset
 * 
 * IER: Interrupt enable register Offset: 0x10
 * - Bit 14 and 15 enable TX and RX interrupts
 *
 * TDR: Transmit data register     Offset: 0x14
 *  - Contains data to be transmitted via UART
 *  TDR[0:8] Byte to be transmited when transmit enable register bit 23 is set to 1.
 *  TDR[9:32] Reserved
 *
 *
 * RDR: Receive data register     Offset: 0x18
 *  - Contains data received via UART
 *
 *
 * This test have 3 tasks. You should be able to answer it in two hours.
 * 
 * 
 * 
 **/

/**
 *  Data structure containing UART parameters including base address and other settings (supressed).
 * */
typedef struct UART_HANDLE {
  /**
   * Base mememory address. To access the correct device memory register address, you need to sum 
   * the base address with the offsets.
   **/
  uint32_t base_mem_addr;
} UART_HANDLE;


/**
  This functions writes to the memory address the value of val.
  \param mem_addr Absolute address to memory.
  \param val Value to be written in memory.
*/
void stub_memwrite(uint32_t mem_addr, uint32_t val)
{
  /* Task 3 (optional): 
    Print the values received
    for char characeters, it's printed its ASCII value
  */
  printf("%d \n", val);
}


/**
  Initialize the UART device.
  \param h Pointer to UART_HANDLE handle;
*/
void init_uart(UART_HANDLE *h)
{
  /* Initialize the handle to be accessed by stubs after that*/
  h->base_mem_addr = 0xFC000000;
  
  /* This function also configure the device using BRR and other registers, 
   *  but that code was supressed here. Consider that this initialization is done here. 
   YOU DO NOT NEED TO FILL THIS FUNCTION. */
}


/**
  Write (send) data to UART device.
  \param h Pointer to UART_HANDLE handle
  \param data Pointer to data that will be sent
  \param size Size in bytes of the data pointer
*/
void write_uart(UART_HANDLE *h, void *data, int size)
{
   /* Task 2: 
   Set the baud rate to 9600
   Cast the void pointer *data to a dereferenceable char pointer *data_content  
   Transmit the content pointed by data_content one byte at a time*/   
   
   stub_memwrite(h->base_mem_addr + 0x4, 9600);   
   
   char* data_content = (char*) data;
   for (int i=0; i<=strlen(data_content); i++){
        stub_memwrite(h->base_mem_addr + 0x14, data_content[i]);
        stub_memwrite(h->base_mem_addr + 0x8, 1);
   }
}


int main(int argc, char *argv[])
{
  UART_HANDLE handle;
  char text[] = "Hello World";
  
  init_uart(&handle);

  /* Task 1: 
  Writing the content of the string text into the uart */
  write_uart(&handle, text, sizeof(text));

  return 0;
}
