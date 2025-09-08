#pragma once
uintptr_t GA123 = (uintptr_t)GetModuleHandleA("GameAssembly.dll");

namespace Unity
{
	struct System_String : il2cppObject
	{
		int m_iLength;
		wchar_t m_wString[1024];

		void Clear()
		{
			if (!this) return;

			memset(m_wString, 0, static_cast<size_t>(m_iLength) * 2);
			m_iLength = 0;
		}

		std::string ToString()
		{
			if (!this) return "";

			std::string sRet(static_cast<size_t>(m_iLength + 1) * 4, '\0');
			WideCharToMultiByte(CP_UTF8, 0, m_wString, m_iLength, &sRet[0], static_cast<int>(sRet.size()), 0, 0);
			return sRet;
		}
	};

	System_String* CreateString(const char* cstr)
	{
		if (!cstr) return nullptr;

		int len = static_cast<int>(strlen(cstr));

		System_String* (__fastcall * t)(int); // peter how are you doing that?
		auto func = reinterpret_cast<decltype(t)>(GA123 + 0x72F1B50); // internal static String FastAllocateString(Int32 length) { }
		t = func;

		System_String* str = t(len);

		// https://stackoverflow.com/questions/28291287/char-type-and-re-encoding-ascii-text-into-utf-16 (ASCII -> UTF-16)
		for (int i = 0; i < len; i++)
			str->m_wString[i] = static_cast<wchar_t>(cstr[i]);

		str->m_wString[len] = 0;

		str->m_iLength = len;

		return str;
	}
}
