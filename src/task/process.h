#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#include "task.h"
#include "config.h"

// TODO(Darleanow): Implem ELF

struct process
{
    // Proc id
    uint16_t id; // TODO(Darleanow): Increase maybe ?

    char filename[ACTARUS_MAX_PATH];

    // The main process task
    struct task *task;

    // Mem (malloc) allocations of the process
    void *allocations[ACTARUS_MAX_PROGRAM_ALLOCATIONS]; // TODO(Darleanow): Increase maybe ?

    // Physical ptr to proc mem
    void *ptr;

    // Physical ptr to stack mem
    void *stack;

    // Size of data pointer to by ptr
    uint32_t size;
};

int process_load(const char *filename, struct process **process);
int process_load_for_slot(const char *filename, struct process **process, int process_slot);

#endif