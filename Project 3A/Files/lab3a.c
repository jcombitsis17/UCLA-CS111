/*
NAME: Jordan Combitsis, Anchal Sinha
EMAIL: jcombitsis17@gmail.com, ***EMAIL HERE***
ID: 004921527, ***ID HERE***
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
#include "ext2_fs.h"

#define SUPERBLOCK_OFFSET 1024

struct ext2_super_block superblock_data;
struct ext2_group_desc group_data;
unsigned int bsize;

int img_fd;

void superblock_summary()
{
    if (pread(img_fd, &superblock_data, sizeof(superblock_data), SUPERBLOCK_OFFSET) == -1) {
        fprintf(stderr, "Error: pread, superblock\n");
        exit(2);
    }

    bsize = EXT2_MIN_BLOCK_SIZE << superblock_data.s_log_block_size;
    fprintf(stdout, "SUPERBLOCK,%d,%d,%d,%d,%d,%d,%d\n",
            superblock_data.s_blocks_count,
            superblock_data.s_inodes_count,
            bsize,
            superblock_data.s_inode_size,
            superblock_data.s_blocks_per_group,
            superblock_data.s_inodes_per_group,
            superblock_data.s_first_ino
    );
}

void free_block_entries(unsigned int bitmap)
{
    char* data_block = malloc(bsize);
    if (pread(img_fd, &data_block, bsize, bsize * (bitmap - 1) + SUPERBLOCK_OFFSET) == -1) {
        fprintf(stderr, "Error: pread, free block entries\n");
        exit(2);
    }

    unsigned int i, bit;
    for (i = 0; i < bsize; i++)
    {
        char byte = data_block[i];
        for (bit = 0; bit < 8; bit++)
        {
            if ( !((byte >> bit) & 1) ) {
                fprintf(stdout, "BFREE,%d\n", /*IDK WHAT TO PUT HERE*/);
            }
        }
    }
    free(data_block);
}

void free_inode_entries(unsigned int bitmap)
{
    char* data_block = malloc(bsize);
    if (pread(img_fd, &data_block, bsize, bsize * (bitmap - 1) + SUPERBLOCK_OFFSET) == -1) {
        fprintf(stderr, "Error: pread, free inode entries\n");
        exit(2);
    }

    unsigned int i, bit;
    for (i = 0; i < bsize; i++)
    {
        char byte = data_block[i];
        for (bit = 0; bit < 8; bit++)
        {
            if ( !((byte >> bit) & 1) ) {
                fprintf(stdout, "IFREE,%d\n", /*IDK WHAT TO PUT HERE*/);
            }
        }
    }
    free(data_block);
}

void group_summary()
{
    if (pread(img_fd, &group_data, sizeof(group_data), bsize + SUPERBLOCK_OFFSET) == -1) {
        fprintf(stderr, "Error: pread, group\n");
        exit(2);
    }

    fprintf(stdout, "GROUP,0,%d,%d,%d,%d,%d,%d,%d\n",
            superblock_data.s_blocks_count,
            superblock_data.s_inodes_count,
            group_data.bg_free_blocks_count,
            group_data.bg_free_inodes_count,
            group_data.bg_block_bitmap,
            group_data.bg_inode_bitmap,
            group_data.bg_inode_table
    );

    // other function(s) here ("...for each group...")
    free_block_entries(group_data.bg_block_bitmap);
    free_inode_entries(group_data.bg_inode_bitmap);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of arguments.\n");
        exit(1);
    }

    img_fd = open(argv[1], O_RDONLY);
    if (img_fd == -1) {
        fprintf(stderr, "Error: Could not open image.\n");
        exit(2);
    }

    superblock_summary();
    group_summary(); // we can assume there will be only a single group for grading

    exit(0);
}