#include "openfile.h"
#include "sysdep.h"
#define FILE_MAX 10
#define CONSOLE_IN 0
#define CONSOLE_OUT 1
#define MODE_READWRITE 0
#define MODE_WRITE 1
#define MODE_READ 2

class FileTable {
   private:
    OpenFile** openFile;
    int* fileOpenMode;
    int* fileDescriptor;

   public:
    FileTable() {
        openFile = new OpenFile*[FILE_MAX];
        fileOpenMode = new int[FILE_MAX];
        fileOpenMode[CONSOLE_IN] = MODE_READ;
        fileOpenMode[CONSOLE_OUT] = MODE_WRITE;

        fileDescriptor = new int[FILE_MAX];
    }

    int Insert(char* fileName, int openMode) {
        int freeIndex = -1;
        for (int i = 2; i < FILE_MAX; i++) {
            if (openFile[i] == NULL) {
                freeIndex = i;
                break;
            }
        }

        if (freeIndex == -1) {
            return -1;
        }

        fileDescriptor[freeIndex] = OpenForReadWrite(fileName, FALSE);

        if (fileDescriptor[freeIndex] == -1) return -1;
        openFile[freeIndex] = new OpenFile(fileDescriptor[freeIndex]);
        fileOpenMode[freeIndex] = openMode;

        return freeIndex;
    }

    int Remove(int index) {
        if (index < 2 || index >= FILE_MAX) return -1;
        if (openFile[index]) {
            Close(fileDescriptor[index]);
            openFile[index] = NULL;
            return 0;
        }
        return -1;
    }

    ~FileTable() {
        for (int i = 0; i < FILE_MAX; i++) {
            if (openFile[i]) delete openFile[i];
        }
        delete[] openFile;
    }
};