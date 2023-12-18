#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

void handleError(const char* message) {
    fprintf(stderr, "Error: %s\n", message);
}

DWORD executeProcessAndGetExitCode(const char* executable, const char* argument) {
    STARTUPINFOA startupInfo;
    PROCESS_INFORMATION processInfo;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory(&processInfo, sizeof(processInfo));

    char commandLine[256];
    _snprintf_s(commandLine, sizeof(commandLine), _TRUNCATE, "\"%s\" %s", executable, argument);

    if (!CreateProcessA(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
        handleError("Failed to create process");
        return 1;
    }

    WaitForSingleObject(processInfo.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(processInfo.hProcess, &exitCode);

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return exitCode;
}

int main(int argCount, char* argValues[]) {
    if (argCount != 2) {
        handleError("Invalid argument count (max 1)");
        return 1;
    }

    int argLen = strlen(argValues[1]);
    if (argLen < 1 || argLen > 25) {
        handleError("Invalid argument length (1 to 25)");
        return 1;
    }

    for (int i = 0; argValues[1][i] != '\0'; i++) {
        if (!isdigit(argValues[1][i])) {
            handleError("Argument contains non-digit characters");
            return 1;
        }
    }

    if (argLen == 1) {
        return argValues[1][0] - '0';
    }

    int halfLen = argLen / 2;
    char* upperHalf = (char*)malloc(halfLen + 1);
    char* lowerHalf = (char*)malloc(argLen - halfLen + 1);

    strncpy_s(upperHalf, halfLen + 1, argValues[1], _TRUNCATE);
    strncpy_s(lowerHalf, argLen - halfLen + 1, argValues[1] + halfLen, _TRUNCATE);

    upperHalf[halfLen] = '\0';
    lowerHalf[argLen - halfLen] = '\0';

    DWORD exit1 = executeProcessAndGetExitCode(argValues[0], upperHalf);
    DWORD exit2 = executeProcessAndGetExitCode(argValues[0], lowerHalf);

    printf("%d %d %s %d\n", GetCurrentProcessId(), GetCurrentProcessId(), upperHalf, exit1);
    printf("%d %d %s %d\n", GetCurrentProcessId(), GetCurrentProcessId(), lowerHalf, exit2);

    free(upperHalf);
    free(lowerHalf);

    return exit1 + exit2;
}
