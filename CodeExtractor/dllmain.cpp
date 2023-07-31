#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>

#define WEAPON_FILE_NAME "_weapon_code.txt"
#define CHAR_FILE_NAME "_char_code.txt"

HMODULE hCurrentModule;

typedef INT64(fGetItemIndex)(INT64 Param, DWORD Code);
typedef INT64(fGetParam)(void);
typedef INT64(fGetItemName)(INT64 Param, DWORD Type, DWORD _, DWORD Code, DWORD Index);

INT64 cshell_base;
fGetItemIndex* f_GetWeaponItemIndex;
fGetItemIndex* f_GetCharItemIndex;
fGetParam* f_GetParam;
fGetItemName* f_GetItemName;

/*
cshell.dll+494EC1 - E8 DA8BCEFF           - call cshell.dll+17DAA0
cshell.dll+494EC6 - 84 C0                 - test al,al
cshell.dll+494EC8 - 0F85 EF050000         - jne cshell.dll+4954BD
cshell.dll+494ECE - 41 8B D5              - mov edx,r13d
cshell.dll+494ED1 - 48 8B 0D 784D1301     - mov rcx,[cshell.dll+15C9C50] { (7FF9F1349E10) } <<
cshell.dll+494ED8 - E8 831D5300           - call cshell.dll+9C6C60 <<
cshell.dll+494EDD - 4C 8B F8              - mov r15,rax
cshell.dll+494EE0 - 48 85 C0              - test rax,rax
cshell.dll+494EE3 - 0F84 56050000         - je cshell.dll+49543F
cshell.dll+494EE9 - 8B 10                 - mov edx,[rax]
cshell.dll+494EEB - 48 8B 0D 5E4D1301     - mov rcx,[cshell.dll+15C9C50] { (7FF9F1349E10) }
cshell.dll+494EF2 - E8 19335300           - call cshell.dll+9C8210
cshell.dll+494EF7 - 45 33 F6              - xor r14d,r14d
cshell.dll+494EFA - 3C 01                 - cmp al,01 { 1 }
cshell.dll+494EFC - 0F85 BE020000         - jne cshell.dll+4951C0
*/

DWORD GetWeaponItemIndex(DWORD Code) {
    INT64 Param = *(INT64*)(cshell_base + 0x15C9C50);
    INT64 ItemInfoBase = f_GetWeaponItemIndex(Param, Code);
    if (ItemInfoBase)
        return *(DWORD*)(ItemInfoBase + 0xFD8);
    return 0;
}

/*
cshell.dll+D94FA4 - E8 578CF2FF           - call cshell.dll+CBDC00
cshell.dll+D94FA9 - 48 8B 0D A8108400     - mov rcx,[cshell.dll+15D6058] { (7FF9F1356500) } <<
cshell.dll+D94FB0 - 8B D7                 - mov edx,edi
cshell.dll+D94FB2 - 48 8B D8              - mov rbx,rax
cshell.dll+D94FB5 - E8 B6DBD0FF           - call cshell.dll+AA2B70 <<
cshell.dll+D94FBA - 45 33 C0              - xor r8d,r8d
cshell.dll+D94FBD - 89 44 24 20           - mov [rsp+20],eax
cshell.dll+D94FC1 - 44 8B CF              - mov r9d,edi
cshell.dll+D94FC4 - 48 8B CB              - mov rcx,rbx
cshell.dll+D94FC7 - 41 8D 50 03           - lea edx,[r8+03]
cshell.dll+D94FCB - E8 E08FF2FF           - call cshell.dll+CBDFB0
cshell.dll+D94FD0 - B9 01040000           - mov ecx,00000401 { 1025 }
cshell.dll+D94FD5 - 48 8B D8              - mov rbx,rax
cshell.dll+D94FD8 - E8 6388F2FF           - call cshell.dll+CBD840
cshell.dll+D94FDD - 4C 8B C3              - mov r8,rbx
cshell.dll+D94FE0 - 48 8D 4C 24 40        - lea rcx,[rsp+40]
cshell.dll+D94FE5 - 48 8B D0              - mov rdx,rax
cshell.dll+D94FE8 - E8 037F28FF           - call cshell.dll+1CEF0
cshell.dll+D94FED - 48 8B 0D 34F88300     - mov rcx,[cshell.dll+15D4828] { (7FF9F12BB1A8) }
cshell.dll+D94FF4 - 48 8D 54 24 40        - lea rdx,[rsp+40]
cshell.dll+D94FF9 - 33 C0                 - xor eax,eax
cshell.dll+D94FFB - 45 33 C9              - xor r9d,r9d
cshell.dll+D94FFE - 89 44 24 30           - mov [rsp+30],eax
cshell.dll+D95002 - 45 33 C0              - xor r8d,r8d
cshell.dll+D95005 - 89 44 24 28           - mov [rsp+28],eax
cshell.dll+D95009 - 48 89 44 24 20        - mov [rsp+20],rax
*/

DWORD GetCharItemIndex(DWORD Code) {
    INT64 Param = *(INT64*)(cshell_base + 0x15D6058);
    return f_GetCharItemIndex(Param, Code);
}

/*
cshell.dll+495294 - 48 81 FA 00100000     - cmp rdx,00001000 { 4096 }
cshell.dll+49529B - 72 1C                 - jb cshell.dll+4952B9
cshell.dll+49529D - 48 83 C2 27           - add rdx,27 { 39 }
cshell.dll+4952A1 - 48 8B 49 F8           - mov rcx,[rcx-08]
cshell.dll+4952A5 - 48 2B C1              - sub rax,rcx
cshell.dll+4952A8 - 48 83 C0 F8           - add rax,-08 { 248 }
cshell.dll+4952AC - 48 83 F8 1F           - cmp rax,1F { 31 }
cshell.dll+4952B0 - 76 07                 - jna cshell.dll+4952B9
cshell.dll+4952B2 - FF 15 601FC700        - call qword ptr [cshell.dll+1107218] { ->ucrtbase.invalid_parameter_noinfo_noreturn }
cshell.dll+4952B8 - CC                    - int 3
cshell.dll+4952B9 - E8 4A9BBD00           - call cshell.dll+106EE08
cshell.dll+4952BE - E8 3D898200           - call cshell.dll+CBDC00 <<
cshell.dll+4952C3 - 41 8B 8F D80F0000     - mov ecx,[r15+00000FD8] <<
cshell.dll+4952CA - 89 4C 24 20           - mov [rsp+20],ecx
cshell.dll+4952CE - 45 8B 0F              - mov r9d,[r15]
cshell.dll+4952D1 - 45 33 C0              - xor r8d,r8d
cshell.dll+4952D4 - 41 8D 50 02           - lea edx,[r8+02]
cshell.dll+4952D8 - 48 8B C8              - mov rcx,rax
cshell.dll+4952DB - E8 D08C8200           - call cshell.dll+CBDFB0 <<
cshell.dll+4952E0 - 4C 8B C0              - mov r8,rax
cshell.dll+4952E3 - 48 8D 15 F676D100     - lea rdx,[cshell.dll+11AC9E0] { (-121444928) }
cshell.dll+4952EA - 48 8D 4D E0           - lea rcx,[rbp-20]
cshell.dll+4952EE - E8 FD7BB8FF           - call cshell.dll+1CEF0
cshell.dll+4952F3 - 48 8B 05 5E441301     - mov rax,[cshell.dll+15C9758] { (7FF9F12991C0) }
cshell.dll+4952FA - 83 B8 E0E90000 36     - cmp dword ptr [rax+0000E9E0],36 { 54 }
cshell.dll+495301 - 75 47                 - jne cshell.dll+49534A
cshell.dll+495303 - 41 83 3F 00           - cmp dword ptr [r15],00 { 0 }
cshell.dll+495307 - 75 41                 - jne cshell.dll+49534A
cshell.dll+495309 - 41 B8 01000000        - mov r8d,00000001 { 1 }
cshell.dll+49530F - 48 8D 15 C2ECD000     - lea rdx,[cshell.dll+11A3FD8] { ("sa_interface2\hud\HAndSStealth\Ghosts.dtx") }
*/

void _main() {
    while (!cshell_base) {
        Sleep(100);
        cshell_base = (INT64)GetModuleHandleA("cshell.dll");
    }

    f_GetWeaponItemIndex = (fGetItemIndex*)(cshell_base + 0x9C6C60);
    f_GetCharItemIndex = (fGetItemIndex*)(cshell_base + 0xAA2B70);
    f_GetParam = (fGetParam*)(cshell_base + 0xCBDC00);
    f_GetItemName = (fGetItemName*)(cshell_base + 0xCBDFB0);

    FILE* fWeapon = fopen(WEAPON_FILE_NAME, "w");
    FILE* fChar = fopen(CHAR_FILE_NAME, "w");

    for (DWORD i = 0; i < 6000; i++) {
        __try {
            INT64 Param = f_GetParam();

            INT64 pWeaponName = f_GetItemName(Param, 2, 0, i, GetWeaponItemIndex(i));
            if (pWeaponName)
                fprintf(fWeapon, "%d | %s\n", i, (char*)pWeaponName);

            INT64 pCharName = f_GetItemName(Param, 3, 0, i, GetCharItemIndex(i));
            if (pCharName)
                fprintf(fChar, "%d | %s\n", i, (char *)pCharName);
        } 
        __except(1) {}
    }

    fclose(fWeapon);
    fclose(fChar);

    FreeLibraryAndExitThread(hCurrentModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hCurrentModule = hModule;
        DWORD ThreadId;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)_main, NULL, 0, &ThreadId);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

