#include "openfile.h"
#include "sysdep.h"

#define FILE_MAX 10
#define CONSOLE_IN 0
#define CONSOLE_OUT 1
#define MODE_READWRITE 0
#define MODE_READ 1
#define MODE_WRITE 2

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

        if (openMode == MODE_READWRITE)
            fileDescriptor[freeIndex] = OpenForReadWrite(fileName, FALSE);
        if (openMode == MODE_READ)
            fileDescriptor[freeIndex] = OpenForRead(fileName, FALSE);

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

    int Read(char* buffer, int charCount, int index) {
        if (index >= FILE_MAX) return -1;
        if (openFile[index] == NULL) return -1;
        int result = openFile[index]->Read(buffer, charCount);
        // if we cannot read enough bytes, we should return -2
        if (result != charCount) return -2;
        return result;
    }

    int Write(char* buffer, int charCount, int index) {
        if (index >= FILE_MAX) return -1;
        if (openFile[index] == NULL || fileOpenMode[index] == MODE_READ)
            return -1;
        return openFile[index]->Write(buffer, charCount);
    }

    int Seek(int pos, int index) {
        if (index <= 1 || index >= FILE_MAX) return -1;
        if (openFile[index] == NULL) return -1;
        // use seek(-1) to move to the end of file
        if (pos == -1) pos = openFile[index]->Length();
        if (pos < 0 || pos > openFile[index]->Length()) return -1;
        return openFile[index]->Seek(pos);
    }

    ~FileTable() {
        for (int i = 0; i < FILE_MAX; i++) {
            if (openFile[i]) delete openFile[i];
        }
        delete[] openFile;
    }
};
