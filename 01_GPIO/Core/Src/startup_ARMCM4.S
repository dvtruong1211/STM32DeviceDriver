.syntax unified
.arch armv7e-m

.section .stack
.align 3
.equ Stack_Size, 0x00001000
.globl __StackTop
.globl __StackLimit
__StackLimit:
    .space Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

.section .heap
.align 3
.equ Heap_Size, 0x00001000
.globl __HeapBase
.globl __HeapLimit
__HeapBase:
    .if Heap_Size
    .space Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

.section .vectors
.align 2
.globl __Vectors
__Vectors:
                .long    __StackTop                         /*     Top of Stack */
                .long    Reset_Handler                      /*     Reset Handler */
                .long    NMI_Handler                        /* -14 NMI Handler */
                .long    HardFault_Handler                  /* -13 Hard Fault Handler */
                .long    MemManage_Handler                  /* -12 MPU Fault Handler */
                .long    BusFault_Handler                   /* -11 Bus Fault Handler */
                .long    UsageFault_Handler                 /* -10 Usage Fault Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SVC_Handler                        /*  -5 SVC Handler */
                .long    DebugMon_Handler                   /*  -4 Debug Monitor Handler */
                .long    0                                  /*     Reserved */
                .long    PendSV_Handler                     /*  -2 PendSV Handler */
                .long    SysTick_Handler                    /*  -1 SysTick Handler */

    /* External interrupt*/
                .long    Reserved_Handler                   /*  0  */
                .long    Reserved_Handler                   /*  1  */
                .long    Reserved_Handler                   /*  2  */
                .long    Reserved_Handler                   /*  3  */
                .long    Reserved_Handler                   /*  4  */
                .long    Reserved_Handler                   /*  5  */
                .long    EXTI0_IRQHandler                   /*  6  */
                .long    Reserved_Handler                   /*  7  */
                .long    Reserved_Handler                   /*  8  */
                .long    Reserved_Handler                   /*  9  */
                .long    Reserved_Handler                   /* 10  */
                .long    Reserved_Handler                   /* 11  */
                .long    Reserved_Handler                   /* 12  */
                .long    Reserved_Handler                   /* 13  */
                .long    Reserved_Handler                   /* 14  */
                .long    Reserved_Handler                   /* 15  */
                .long    Reserved_Handler                   /* 16  */
                .long    Reserved_Handler                   /* 17  */
                .long    Reserved_Handler                   /* 18  */
                .long    Reserved_Handler                   /* 19  */
                .long    Reserved_Handler                   /* 20  */
                .long    Reserved_Handler                   /* 21  */
                .long    Reserved_Handler                   /* 22  */
                .long    Reserved_Handler                   /* 23  */
                .long    Reserved_Handler                   /* 24  */
                .long    Reserved_Handler                   /* 25  */
                .long    Reserved_Handler                   /* 26  */
                .long    Reserved_Handler                   /* 27  */
                .long    Reserved_Handler                   /* 28  */
                .long    Reserved_Handler                   /* 29  */
                .long    Reserved_Handler                   /* 30  */
                .long    Reserved_Handler                   /* 31  */
                .long    Reserved_Handler                   /* 32  */
                .long    Reserved_Handler                   /* 33  */
                .long    Reserved_Handler                   /* 34  */
                .long    Reserved_Handler                   /* 35  */
                .long    Reserved_Handler                   /* 36  */
                .long    Reserved_Handler                   /* 37  */
                .long    Reserved_Handler                   /* 38  */
                .long    Reserved_Handler                   /* 39  */
                .long    Reserved_Handler                   /* 40  */
                .long    Reserved_Handler                   /* 41  */
                .long    Reserved_Handler                   /* 42  */
                .long    Reserved_Handler                   /* 43  */
                .long    Reserved_Handler                   /* 44  */
                .long    Reserved_Handler                   /* 45  */
                .long    Reserved_Handler                   /* 46  */
                .long    Reserved_Handler                   /* 47  */
                .long    Reserved_Handler                   /* 48  */
                .long    Reserved_Handler                   /* 49  */
                .long    Reserved_Handler                   /* 50  */
                .long    Reserved_Handler                   /* 51  */
                .long    Reserved_Handler                   /* 52  */
                .long    Reserved_Handler                   /* 53  */
                .long    Reserved_Handler                   /* 54  */
                .long    Reserved_Handler                   /* 55  */
                .long    Reserved_Handler                   /* 56  */
                .long    Reserved_Handler                   /* 57  */
                .long    Reserved_Handler                   /* 58  */
                .long    Reserved_Handler                   /* 59  */
                .long    Reserved_Handler                   /* 60  */
                .long    Reserved_Handler                   /* 61  */
                .long    Reserved_Handler                   /* 62  */
                .long    Reserved_Handler                   /* 63  */
                .long    Reserved_Handler                   /* 64  */
                .long    Reserved_Handler                   /* 65  */
                .long    Reserved_Handler                   /* 66  */
                .long    Reserved_Handler                   /* 67  */
                .long    Reserved_Handler                   /* 68  */
                .long    Reserved_Handler                   /* 69  */
                .long    Reserved_Handler                   /* 70  */
                .long    Reserved_Handler                   /* 71  */
                .long    Reserved_Handler                   /* 72  */
                .long    Reserved_Handler                   /* 73  */
                .long    Reserved_Handler                   /* 74  */
                .long    Reserved_Handler                   /* 75  */
                .long    Reserved_Handler                   /* 76  */
                .long    Reserved_Handler                   /* 77  */
                .long    Reserved_Handler                   /* 78  */
                .long    Reserved_Handler                   /* 79  */
                .long    Reserved_Handler                   /* 80  */
                .long    Reserved_Handler                   /* 81  */
                .long    Reserved_Handler                   /* 82  */
                .long    Reserved_Handler                   /* 83  */
                .long    Reserved_Handler                   /* 84  */
                .long    Reserved_Handler                   /* 85  */

__Vectors_End:
    .size __Vectors, . - __Vectors

.text
.thumb
.thumb_func
.align 1
.globl Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* Khởi tạo hệ thống (nếu cần) */
    bl SystemInit

    /* Sao chép dữ liệu khởi đầu (nếu cần) */
    ldr r4, =__copy_table_start__
    ldr r5, =__copy_table_end__

.L_loop0:
    /* ... Sao chép dữ liệu ... */

/* Bỏ qua phần xử lý dữ liệu zero (nếu cần) */

    /* Gọi hàm _start */
    bl _start

    /* Lặp vô hạn nếu chương trình kết thúc */
.endloop:
    b .

/* Khai báo các trình xử lý ngoại lệ (nếu cần) */

/* ... */

/* Định nghĩa hàm _start */
.thumb_func
.type _start, %function
.globl _start
_start:
    /* Thực hiện các khởi tạo ban đầu */

    /* Gọi hàm main */
    bl main

    /* Kết thúc chương trình */
    b .

/* Khai báo các trình xử lý ngoại lệ khác (nếu cần) */

/* ... */

/* Các khai báo tiếp theo (nếu có) */
