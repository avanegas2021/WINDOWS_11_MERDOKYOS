#include <windows.h>
#include <stdio.h>

int main() {
    SIZE_T size = 4096; // Size of memory to allocate (4 KB)

    // Step 1: Allocate virtual memory (reserve + commit)
    void* mem = VirtualAlloc(
        NULL,                    // Let the system determine the address
        size,                    // Size of memory to allocate
        MEM_COMMIT | MEM_RESERVE, // Reserve and commit memory at once
        PAGE_READWRITE           // Allow read and write access to the memory
    );

    // Step 2: Check if allocation was successful
    if (mem == NULL) {
        printf("VirtualAlloc failed: %lu\n", GetLastError());
        return 1;
    }

    printf("Memory allocated successfully at address: %p\n", mem);

    // Step 3: Use the allocated memory (example: initialize it)
    memset(mem, 0x00, size); // Fill the memory with zeros

    // You can now use 'mem' like a normal buffer...

    // Step 4: Free the memory when done
    if (!VirtualFree(mem, 0, MEM_RELEASE)) {
        printf("VirtualFree failed: %lu\n", GetLastError());
        return 1;
    }

    printf("Memory freed successfully.\n");

    return 0;
}
