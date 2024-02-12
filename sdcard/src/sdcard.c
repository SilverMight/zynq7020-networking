#include "ff.h"

#include "xil_printf.h"
#include "xstatus.h"

#include "sdcard.h"

int sdcard_mount(FATFS *fs) {
	FRESULT rc;
	TCHAR *Path = "";

	rc = f_mount(fs, Path, (BYTE) 0);

	// error check
	if(rc) {
		xil_printf("f_mount returned %d\n", rc);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int sdcard_eject() {
	FRESULT rc;
	TCHAR *Path = "";

	rc = f_mount(0, Path, (BYTE) 0);

	// error check
	if(rc) {
		xil_printf("f_mount returned %d\n", rc);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int file_open(FIL *fp, TCHAR *path) {
	FRESULT rc;
	rc = f_open(fp, path, FA_OPEN_ALWAYS);

	if(rc) {
		xil_printf("Failed to open file %d\n", rc);
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int file_write(FIL *fp, const void* buff, UINT bytesToWrite) {
	FRESULT rc;
	UINT bytesWritten;

	rc = f_write(fp, buff, bytesToWrite, &bytesWritten);

	if(bytesToWrite < bytesWritten) {
		xil_printf("Didn't write all bytes, is disk full?\n");
	}

	if(rc) {
		xil_printf("Failed to write to file %d\n", rc);
	}

	return XST_SUCCESS;
}
