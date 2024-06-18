#include <windows.h>
#include <synchapi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2 || strlen(argv[1]) < 1 || strlen(argv[1]) > 25) {
        fprintf(stderr, "Error: Invalid arg\n");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (!isdigit(argv[1][i])) {
            fprintf(stderr, "Error: Arg not num\n");
            return 1;
        }
    }

    int len = strlen(argv[1]);
    if (len == 1) {
        return argv[1][0] - '0';
    }

    int hLen = len / 2;
    char* h1 = (char*)malloc(hLen + 1); // reserve the memory
    strncpy_s(h1, hLen + 1, argv[1], _TRUNCATE); // _TRUNCATE = ((size_t)-1)
    h1[hLen] = '\0';
    char* h2 = (char*)malloc(len - hLen + 1);
    strncpy_s(h2, len - hLen + 1, argv[1] + hLen, _TRUNCATE);
    h2[len - hLen] = '\0';

// specializes window station, desktop, standard handles,
    STARTUPINFOA si1, si2; // and appearance of the main window for a process at creation time.

    PROCESS_INFORMATION pi1, pi2; // information about a newly created process and its primary thread

//  fills a block of memory with zeros zeby wszystkie zmienne byly zainicjalizowane
    ZeroMemory(&si1, sizeof(si1));
    ZeroMemory(&si2, sizeof(si2));
    ZeroMemory(&pi1, sizeof(pi1));
    ZeroMemory(&pi2, sizeof(pi2));

    char cmd1[256], cmd2[256];
    _snprintf_s(cmd1, sizeof(cmd1), _TRUNCATE, "\"%s\" %s", argv[0], h1);
    _snprintf_s(cmd2, sizeof(cmd2), _TRUNCATE, "\"%s\" %s", argv[0], h2);

    // Creates a new process and its primary thread.
    // The new process runs in the security context of the calling process.
    if (!CreateProcessA(NULL, cmd1, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1) || !CreateProcessA(NULL, cmd2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)) {
        fprintf(stderr, "Error: Creating processes (%lu)\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    DWORD e1, e2; // special windows data format, 2*word (2*16 bit presumably)
    GetExitCodeProcess(pi1.hProcess, &e1); // store the exit code in e`n`
    GetExitCodeProcess(pi2.hProcess, &e2);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    printf("%lu ", GetCurrentProcessId());
    printf("%lu ", pi1.dwProcessId);
    printf("%s ", h1);
    printf("%lu \n", e1);

    printf("%lu ", GetCurrentProcessId());
    printf("%lu ", pi2.dwProcessId);
    printf("%s ", h2);
    printf("%lu \n", e2);

    free(h1);
    free(h2);

    return e1 + e2;
}
