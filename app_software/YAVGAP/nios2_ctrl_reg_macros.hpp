#ifndef __NIOS2_CTRL_REG_MACROS__
#define __NIOS2_CTRL_REG_MACROS__

/*****************************************************************************/
/* Macros for accessing the control registers.                               */
/*****************************************************************************/

#define NIOS2_READ_STATUS(dest)   { dest = __builtin_rdctl(0); }
#define NIOS2_WRITE_STATUS(src)   { __builtin_wrctl(0, src);   }
#define NIOS2_READ_ESTATUS(dest)  { dest = __builtin_rdctl(1); }
#define NIOS2_READ_BSTATUS(dest)  { dest = __builtin_rdctl(2); }
#define NIOS2_READ_IENABLE(dest)  { dest = __builtin_rdctl(3); }
#define NIOS2_WRITE_IENABLE(src)  { __builtin_wrctl(3, src);   }
#define NIOS2_READ_IPENDING(dest) { dest = __builtin_rdctl(4); }
#define NIOS2_READ_CPUID(dest)    { dest = __builtin_rdctl(5); }

#endif
