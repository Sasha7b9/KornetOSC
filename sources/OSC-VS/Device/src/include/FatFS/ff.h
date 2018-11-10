#pragma once
#include "defines.h"
#include "ffconf.h"


typedef struct {
    BYTE	fs_type;		/* File system type (0:N/A) */
    BYTE	drv;			/* Physical drive number */
    BYTE	n_fats;			/* Number of FATs (1 or 2) */
    BYTE	wflag;			/* win[] flag (b0:dirty) */
    BYTE	fsi_flag;		/* FSINFO flags (b7:disabled, b0:dirty) */
    WORD	id;				/* File system mount ID */
    WORD	n_rootdir;		/* Number of root directory entries (FAT12/16) */
    WORD	csize;			/* Cluster size [sectors] */
#if _MAX_SS != _MIN_SS
    WORD	ssize;			/* Sector size (512, 1024, 2048 or 4096) */
#endif
#if _USE_LFN != 0
    WCHAR*	lfnbuf;			/* LFN working buffer */
#endif
#if _FS_EXFAT
    BYTE*	dirbuf;			/* Directory entry block scratchpad buffer */
#endif
#if _FS_REENTRANT
    _SYNC_t	sobj;			/* Identifier of sync object */
#endif
#if !_FS_READONLY
    DWORD	last_clst;		/* Last allocated cluster */
    DWORD	free_clst;		/* Number of free clusters */
#endif
#if _FS_RPATH != 0
    DWORD	cdir;			/* Current directory start cluster (0:root) */
#if _FS_EXFAT
    DWORD	cdc_scl;		/* Containing directory start cluster (invalid when cdir is 0) */
    DWORD	cdc_size;		/* b31-b8:Size of containing directory, b7-b0: Chain status */
    DWORD	cdc_ofs;		/* Offset in the containing directory (invalid when cdir is 0) */
#endif
#endif
    DWORD	n_fatent;		/* Number of FAT entries (number of clusters + 2) */
    DWORD	fsize;			/* Size of an FAT [sectors] */
    DWORD	volbase;		/* Volume base sector */
    DWORD	fatbase;		/* FAT base sector */
    DWORD	dirbase;		/* Root directory base sector/cluster */
    DWORD	database;		/* Data base sector */
    DWORD	winsect;		/* Current sector appearing in the win[] */
    BYTE	win[_MAX_SS];	/* Disk access window for Directory, FAT (and file data at tiny cfg) */
} FATFS;


typedef struct {
    FATFS*	fs;			/* Pointer to the owner file system object */
    WORD	id;			/* Owner file system mount ID */
    BYTE	attr;		/* Object attribute */
    BYTE	stat;		/* Object chain status (b1-0: =0:not contiguous, =2:contiguous (no data on FAT), =3:flagmented in this session, b2:sub-directory stretched) */
    DWORD	sclust;		/* Object start cluster (0:no cluster or root directory) */
    FSIZE_t	objsize;	/* Object size (valid when sclust != 0) */
#if _FS_EXFAT
    DWORD	n_cont;		/* Size of first fragment, clusters - 1 (valid when stat == 3) */
    DWORD	n_frag;		/* Size of last fragment needs to be written (valid when not zero) */
    DWORD	c_scl;		/* Containing directory start cluster (valid when sclust != 0) */
    DWORD	c_size;		/* b31-b8:Size of containing directory, b7-b0: Chain status (valid when c_scl != 0) */
    DWORD	c_ofs;		/* Offset in the containing directory (valid when sclust != 0 and non-directory object) */
#endif
#if _FS_LOCK != 0
    UINT	lockid;		/* File lock ID origin from 1 (index of file semaphore table Files[]) */
#endif
} _FDID;


typedef struct {
    _FDID	obj;			/* Object identifier */
    DWORD	dptr;			/* Current read/write offset */
    DWORD	clust;			/* Current cluster */
    DWORD	sect;			/* Current sector (0:Read operation has terminated) */
    BYTE*	dir;			/* Pointer to the directory item in the win[] */
    BYTE	fn[12];			/* SFN (in/out) {body[8],ext[3],status[1]} */
#if _USE_LFN != 0
    DWORD	blk_ofs;		/* Offset of current entry block being processed (0xFFFFFFFF:Invalid) */
#endif
#if _USE_FIND
    const TCHAR* pat;		/* Pointer to the name matching pattern */
#endif
} DIR;


typedef struct {
    FSIZE_t	fsize;			/* File size */
    WORD	fdate;			/* Modified date */
    WORD	ftime;			/* Modified time */
    BYTE	fattrib;		/* File attribute */
#if _USE_LFN != 0
    TCHAR	altname[13];			/* Alternative file name */
    TCHAR	fname[_MAX_LFN + 1];	/* Primary file name */
#else
    TCHAR	fname[13];		/* File name */
#endif
} FILINFO;


typedef struct {
    _FDID	obj;			/* Object identifier (must be the 1st member to detect invalid object pointer) */
    BYTE	flag;			/* File status flags */
    BYTE	err;			/* Abort flag (error code) */
    FSIZE_t	fptr;			/* File read/write pointer (Zeroed on file open) */
    DWORD	clust;			/* Current cluster of fpter (invalid when fptr is 0) */
    DWORD	sect;			/* Sector number appearing in buf[] (0:invalid) */
#if !_FS_READONLY
    DWORD	dir_sect;		/* Sector number containing the directory entry */
    BYTE*	dir_ptr;		/* Pointer to the directory entry in the win[] */
#endif
#if _USE_FASTSEEK
    DWORD*	cltbl;			/* Pointer to the cluster link map table (nulled on open, set by application) */
#endif
#if !_FS_TINY
    BYTE	buf[_MAX_SS];	/* File private data read/write window */
#endif
} FIL;
