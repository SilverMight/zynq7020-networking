#ifndef SDCARD_H
#define SDCARD_H


int sdcard_mount(FATFS *fs);

int sdcard_eject();

int file_open(FIL *fp, TCHAR *path);

int file_write(FIL *fp, const void* buff, UINT bytesToWrite);

#endif
