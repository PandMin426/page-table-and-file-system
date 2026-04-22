#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/riscv.h"
#include "kernel/memlayout.h" // Để lấy định nghĩa USYSCALL và struct usyscall

int main(void) {
    // Ép kiểu địa chỉ USYSCALL về con trỏ cấu trúc usyscall
    struct usyscall *u = (struct usyscall *)USYSCALL;
    
    printf("--- BAT DAU TEST TASK 1 ---\n");
    
    // 1. Gọi system call getpid() của hệ điều hành (chạy chậm, tốn context switch)
    int sys_pid = getpid();
    printf("PID lay tu system call: %d\n", sys_pid);
    
    // 2. Đọc trực tiếp từ bộ nhớ dùng chung (chạy siêu tốc độ)
    int mem_pid = u->pid;
    printf("PID doc tu memory USYSCALL: %d\n", mem_pid);
    
    // 3. So sánh kết quả
    if (sys_pid == mem_pid) {
        printf("=> KET QUA: SUCCESS! USYSCALL hoat dong hoan hao!\n");
    } else {
        printf("=> KET QUA: FAILED! Co loi xay ra roi!\n");
    }
    
    exit(0); // Kết thúc chương trình
}
