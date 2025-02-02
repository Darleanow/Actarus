#ifndef DISK_H
#define DISK_H

#include "fs/file.h"

typedef unsigned int ACTARUS_DISK_TYPE;

// Represents a real HD
#define ACTARUS_DISK_TYPE_REAL 0

// TODO(Darleanow): Disk array ? By indexes
struct disk
{
    ACTARUS_DISK_TYPE type;
    int sector_size;

    // Disk id
    int id;

    struct filesystem *filesystem;

    // Private data of fs
    void *fs_private;
};

void disk_search_and_init();
struct disk *disk_get(int index);
int disk_read_block(struct disk *idisk, unsigned int lba, int total, void *buf);

#endif