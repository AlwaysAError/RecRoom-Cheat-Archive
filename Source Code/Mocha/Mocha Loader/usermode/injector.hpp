#pragma once
#include "driver.h"
#include "utils.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

BYTE remote_load_library[96] =
{
	0x48, 0x83, 0xEC, 0x38, 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x44, 0x24, 0x20, 0x48, 0x8B, 0x44, 0x24, 0x20,
	0x83, 0x38, 0x00, 0x75, 0x3D, 0x48, 0x8B, 0x44, 0x24, 0x20, 0xC7, 0x00, 0x01, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x44, 0x24, 0x20, 0x48, 0x8B, 0x40,
	0x08, 0x48, 0x89, 0x44, 0x24, 0x28, 0x48, 0x8B, 0x44, 0x24, 0x20, 0x48, 0x83, 0xC0, 0x18, 0x48, 0x8B, 0xC8, 0xFF, 0x54, 0x24, 0x28, 0x48, 0x8B,
	0x4C, 0x24, 0x20, 0x48, 0x89, 0x41, 0x10, 0x48, 0x8B, 0x44, 0x24, 0x20, 0xC7, 0x00, 0x02, 0x00, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x38, 0xC3, 0xCC
};

BYTE remote_call_dll_main[92] =
{
	0x48, 0x83, 0xEC, 0x38, 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x44, 0x24, 0x20, 0x48, 0x8B, 0x44, 0x24,
	0x20, 0x83, 0x38, 0x00, 0x75, 0x39, 0x48, 0x8B, 0x44, 0x24, 0x20, 0xC7, 0x00, 0x01, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x44, 0x24, 0x20, 0x48,
	0x8B, 0x40, 0x08, 0x48, 0x89, 0x44, 0x24, 0x28, 0x45, 0x33, 0xC0, 0xBA, 0x01, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x44, 0x24, 0x20, 0x48, 0x8B,
	0x48, 0x10, 0xFF, 0x54, 0x24, 0x28, 0x48, 0x8B, 0x44, 0x24, 0x20, 0xC7, 0x00, 0x02, 0x00, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x38, 0xC3, 0xCC
}; DWORD shell_data_offset = 0x6;

typedef struct _load_library_struct
{
	int status;
	uintptr_t fn_load_library_a;
	uintptr_t module_base;
	char module_name[80];
} load_library_struct;

typedef struct _main_struct
{
	int status;
	uintptr_t fn_dll_main;
	HINSTANCE dll_base;
} main_struct;

uintptr_t call_remote_load_library(uint32_t pid, DWORD thread_id, LPCSTR dll_name, SOCKET connection)
{
	HMODULE nt_dll = LoadLibraryW((L"ntdll.dll"));

	PVOID alloc_shell_code = (void*)driver::allocate_memory(connection, pid, 4096, PAGE_EXECUTE_READWRITE);

	DWORD shell_size = sizeof(remote_load_library) + sizeof(load_library_struct);

	PVOID alloc_local = VirtualAlloc(NULL, shell_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	RtlCopyMemory(alloc_local, &remote_load_library, sizeof(remote_load_library));
	uintptr_t shell_data = (uintptr_t)alloc_shell_code + sizeof(remote_load_library);
	*(uintptr_t*)((uintptr_t)alloc_local + shell_data_offset) = shell_data;
	load_library_struct* ll_data = (load_library_struct*)((uintptr_t)alloc_local + sizeof(remote_load_library));
	ll_data->fn_load_library_a = (uintptr_t)LoadLibraryA;
	strcpy_s(ll_data->module_name, 80, dll_name);

	driver::write_memory(connection, pid, (uintptr_t)alloc_shell_code, (uintptr_t)alloc_local, shell_size);

	HHOOK h_hook = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)alloc_shell_code, nt_dll, thread_id);

	while (ll_data->status != 2)
	{
		//printf(("[-] Load Error 14\n"));
		//PostThreadMessage(thread_id, WM_NULL, 0, 0);
		//printf(("[-] Load Error 15\n"));

		driver::read_memory(connection, pid, shell_data, (uintptr_t)ll_data, sizeof(load_library_struct));

		Sleep(10);
	}
	uintptr_t mod_base = ll_data->module_base;

	UnhookWindowsHookEx(h_hook);

	driver::free_memory(connection, pid, (uintptr_t)alloc_shell_code);

	VirtualFree(alloc_local, 0, MEM_RELEASE);

	return mod_base;
}

void call_dll_main(uintptr_t process_id,DWORD thread_id, PVOID dll_base, PIMAGE_NT_HEADERS nt_header, bool hide_dll, SOCKET connection)
{
	HMODULE nt_dll = LoadLibraryW((L"ntdll.dll"));

	PVOID alloc_shell_code = (void*)driver::allocate_memory(connection, process_id, 4096, PAGE_EXECUTE_READWRITE);

	DWORD shell_size = sizeof(remote_call_dll_main) + sizeof(main_struct);
	PVOID alloc_local = VirtualAlloc(NULL, shell_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	RtlCopyMemory(alloc_local, &remote_call_dll_main, sizeof(remote_call_dll_main));
	uintptr_t shell_data = (uintptr_t)alloc_shell_code + sizeof(remote_call_dll_main);
	*(uintptr_t*)((uintptr_t)alloc_local + shell_data_offset) = shell_data;
	main_struct* main_data = (main_struct*)((uintptr_t)alloc_local + sizeof(remote_call_dll_main));
	main_data->dll_base = (HINSTANCE)dll_base;
	main_data->fn_dll_main = ((uintptr_t)dll_base + nt_header->OptionalHeader.AddressOfEntryPoint);

	driver::write_memory(connection, process_id, (uintptr_t)alloc_shell_code, (uintptr_t)alloc_local, shell_size);
	
	HHOOK h_hook = SetWindowsHookEx(WH_MOUSE, (HOOKPROC)alloc_shell_code, nt_dll, thread_id);

	while (main_data->status != 2)
	{
		driver::read_memory(connection, process_id, shell_data, (uintptr_t)main_data, sizeof(main_struct));
		Sleep(10);
	}

	UnhookWindowsHookEx(h_hook);

	driver::free_memory(connection, process_id, (uintptr_t)alloc_shell_code);

	VirtualFree(alloc_local, 0, MEM_RELEASE);
}

PVOID rva_va(uintptr_t rva, PIMAGE_NT_HEADERS nt_head, PVOID local_image)
{
	PIMAGE_SECTION_HEADER p_first_sect = IMAGE_FIRST_SECTION(nt_head);
	for (PIMAGE_SECTION_HEADER p_section = p_first_sect; p_section < p_first_sect + nt_head->FileHeader.NumberOfSections; p_section++)
		if (rva >= p_section->VirtualAddress && rva < p_section->VirtualAddress + p_section->Misc.VirtualSize)
			return (PUCHAR)local_image + p_section->PointerToRawData + (rva - p_section->VirtualAddress);

	return NULL;
}

uintptr_t resolve_func_addr(LPCSTR modname, LPCSTR modfunc)
{
	HMODULE h_module = LoadLibraryExA(modname, NULL, DONT_RESOLVE_DLL_REFERENCES);
	uintptr_t func_offset = (uintptr_t)GetProcAddress(h_module, modfunc);
	func_offset -= (uintptr_t)h_module;
	FreeLibrary(h_module);

	return func_offset;
}

BOOL relocate_image(PVOID p_remote_img, PVOID p_local_img, PIMAGE_NT_HEADERS nt_head)
{
	struct reloc_entry
	{
		ULONG to_rva;
		ULONG size;
		struct
		{
			WORD offset : 12;
			WORD type : 4;
		} item[1];
	};

	uintptr_t delta_offset = (uintptr_t)p_remote_img - nt_head->OptionalHeader.ImageBase;
	if (!delta_offset) return true; else if (!(nt_head->OptionalHeader.DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE)) return false;
	reloc_entry* reloc_ent = (reloc_entry*)rva_va(nt_head->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress, nt_head, p_local_img);
	uintptr_t reloc_end = (uintptr_t)reloc_ent + nt_head->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;

	if (reloc_ent == nullptr)
		return true;

	while ((uintptr_t)reloc_ent < reloc_end && reloc_ent->size)
	{
		DWORD records_count = (reloc_ent->size - 8) >> 1;
		for (DWORD i = 0; i < records_count; i++)
		{
			WORD fix_type = (reloc_ent->item[i].type);
			WORD shift_delta = (reloc_ent->item[i].offset) % 4096;

			if (fix_type == IMAGE_REL_BASED_ABSOLUTE)
				continue;

			if (fix_type == IMAGE_REL_BASED_HIGHLOW || fix_type == IMAGE_REL_BASED_DIR64)
			{
				uintptr_t fix_va = (uintptr_t)rva_va(reloc_ent->to_rva, nt_head, p_local_img);

				if (!fix_va)
					fix_va = (uintptr_t)p_local_img;

				*(uintptr_t*)(fix_va + shift_delta) += delta_offset;
			}
		}

		reloc_ent = (reloc_entry*)((LPBYTE)reloc_ent + reloc_ent->size);
	} return true;
}

BOOL resolve_import(uintptr_t pid,DWORD thread_id, PVOID p_local_img, PIMAGE_NT_HEADERS nt_head, SOCKET connection)
{
	PIMAGE_IMPORT_DESCRIPTOR import_desc = (PIMAGE_IMPORT_DESCRIPTOR)rva_va(nt_head->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, nt_head, p_local_img);
	if (!nt_head->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress || !nt_head->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size)
		return true;

	LPSTR module_name = NULL;
	while ((module_name = (LPSTR)rva_va(import_desc->Name, nt_head, p_local_img)))
	{
		uintptr_t base_image;
		base_image = call_remote_load_library(pid,thread_id, module_name, connection);

		if (!base_image)
			return false;

		PIMAGE_THUNK_DATA ih_data = (PIMAGE_THUNK_DATA)rva_va(import_desc->FirstThunk, nt_head, p_local_img);
		while (ih_data->u1.AddressOfData)
		{
			if (ih_data->u1.Ordinal & IMAGE_ORDINAL_FLAG)
				ih_data->u1.Function = base_image + resolve_func_addr(module_name, (LPCSTR)(ih_data->u1.Ordinal & 0xFFFF));
			else
			{
				IMAGE_IMPORT_BY_NAME* ibn = (PIMAGE_IMPORT_BY_NAME)rva_va(ih_data->u1.AddressOfData, nt_head, p_local_img);
				ih_data->u1.Function = base_image + resolve_func_addr(module_name, (LPCSTR)ibn->Name);
			} ih_data++;
		} import_desc++;
	} return true;
}

void write_sections(uintptr_t pid,PVOID p_module_base, PVOID local_image, PIMAGE_NT_HEADERS nt_head, SOCKET connection)
{
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(nt_head);
	for (WORD sec_cnt = 0; sec_cnt < nt_head->FileHeader.NumberOfSections; sec_cnt++, section++)
	{
		driver::write_memory(connection, pid, ((uintptr_t)p_module_base + section->VirtualAddress), ((uintptr_t)local_image + section->PointerToRawData), section->SizeOfRawData);
	}
}

void erase_discardable_sect(uintptr_t pid,PVOID p_module_base, PIMAGE_NT_HEADERS nt_head, SOCKET connection)
{
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(nt_head);
	for (WORD sec_cnt = 0; sec_cnt < nt_head->FileHeader.NumberOfSections; sec_cnt++, section++)
	{
		if (section->SizeOfRawData == 0)
			continue;

		if (section->Characteristics & IMAGE_SCN_MEM_DISCARDABLE)
		{
			PVOID zero_memory = VirtualAlloc(NULL, section->SizeOfRawData, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			driver::write_memory(connection, pid, ((uintptr_t)p_module_base + section->VirtualAddress), (uintptr_t)zero_memory, section->SizeOfRawData);
			VirtualFree(zero_memory, 0, MEM_RELEASE);
		}
	}
}

void ProtectMemory(uintptr_t process_id,uint64_t addr, uint64_t size, DWORD protect, SOCKET connection)
{
	driver::protect_memory(connection, process_id, (uint64_t)addr, size, protect);
}

bool inject(LPCWSTR dll_path, SOCKET connection)
{
	std::wstring wFilePath(dll_path);
	std::filesystem::path pathObj(wFilePath);
	std::wstring filename = pathObj.filename().wstring();

	// get dll file
	PVOID dll_image = get_dll_by_file(dll_path);
	if (!dll_image) 
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::wcout << "[!] Invalid Mod \"" << filename << "\"!\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		return false;
	}

	// parse nt header
	PIMAGE_NT_HEADERS dll_nt_head = RtlImageNtHeader(dll_image);
	if (!dll_nt_head) 
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("[!] Error Code 0x10!\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		return false;
	}

	DWORD thread_id;
	DWORD process_id = get_process_id_and_thread_id_by_window_class("UnityWndClass", &thread_id);

	if (process_id != 0 && thread_id != 0)
	{
		PVOID allocate_base = (void*)driver::allocate_memory(connection, process_id, dll_nt_head->OptionalHeader.SizeOfImage, PAGE_EXECUTE_READWRITE);

		auto endAddr = (uint64_t)((uint64_t)allocate_base + dll_nt_head->OptionalHeader.SizeOfImage);

		/* not needed
		* ProtectMemory((HANDLE)process_id,(uint64_t)allocate_base, 1024, PAGE_READWRITE);
		* ProtectMemory((HANDLE)process_id,(uint64_t)endAddr - 30000, 1024, PAGE_READWRITE);
		*/

		// fix reloc
		if (!relocate_image(allocate_base, dll_image, dll_nt_head))
		{
			driver::free_memory(connection, process_id, (uintptr_t)allocate_base);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("[!] Error Code: 0x11\n");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}

		// fix iat
		if (!resolve_import(process_id,thread_id, dll_image, dll_nt_head, connection))
		{
			driver::free_memory(connection, process_id, (uintptr_t)allocate_base);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("[!] Error Code: 0x12\n");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			return false;
		}

		// write dll section's
		write_sections(process_id,allocate_base, dll_image, dll_nt_head, connection);

		// call dll main
		call_dll_main(process_id,thread_id, allocate_base, dll_nt_head, false, connection);

		// cleanup
		erase_discardable_sect(process_id,allocate_base, dll_nt_head, connection);
		VirtualFree(dll_image, 0, MEM_RELEASE);

		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::wcout << "[+] Successfully Loaded " << filename << "!\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("[!] Process Not Found!\n");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		return false;
	}
}


