#ifndef __DEFS_H
#define __DEFS_H

#include <unistd.h>
#include <inttypes.h>
#include <string>
#include <unordered_map>
#include <dlfcn.h>
#include <sys/stat.h>

#include "log.h"

//
/* A class to wrap loading of a shared library. Any number of function pointers
 * (and their function ptr types) should be allowed for later calling.
 */
class DLLWrapper
{
public:
    //
    DLLWrapper(const char *_dll_filename) :
		m_dllFilename(std::string(_dll_filename))
    {
		reload();
    }
    //
    ~DLLWrapper()
    {
		if (dlclose(m_dllPtr) != 0)
			DLL_ERROR;
		TRACE_INFO("DLL '%s' unloaded.\n", m_dllFilename.c_str());
    }
    // returns true if dll was reloaded, false otherwise
    bool reload()
    {
		// check for file modification
		struct stat st;
		if (stat(m_dllFilename.c_str(), &st) != 0)
			TRACE_ERROR("could not get file statistics for '%s'.\n", m_dllFilename.c_str());
		if (m_dllCTime != st.st_mtime)
		{
			// TRACE_INFO("reloading DLL '%s'.\n", m_dllFilename.c_str());
			m_dllCTime = st.st_mtime;
		}
		else
			return false;
	
		//
		release();
        usleep(500*1000);

		//
		if ((m_dllPtr = dlopen(m_dllFilename.c_str(), RTLD_NOW)) == NULL) DLL_ERROR;

		// reset symbols
		for (auto& it : m_funcPtrs)
		{
			void *func_ptr = (void*)dlsym(m_dllPtr, it.first.c_str());
			if (func_ptr == NULL) DLL_ERROR;
			m_funcPtrs[it.first] = func_ptr;
		}

		return true;
    }
    //
    void release()
    {
		if (m_dllPtr != NULL)
			dlclose(m_dllPtr);
    }
    //
    void addSymbol(const char *_sym_name)
    {
		void *fptr = dlsym(m_dllPtr, _sym_name);
		if (fptr == NULL)
			DLL_ERROR;
		TRACE_INFO("added function pointer for dll function '%s'.\n", _sym_name);
		m_funcPtrs.insert({ std::string(_sym_name), fptr });
    }
    //
    template<typename T, typename ...Args>
    void call(const char *_func, Args... args)
    {
		((T)m_funcPtrs[_func])(args...);
    }

	const char *filename() { return m_dllFilename.c_str(); }

private:
    std::string m_dllFilename = "";
    void* m_dllPtr = NULL;
    std::unordered_map<std::string, void*> m_funcPtrs;
    __time_t m_dllCTime = 0;

};



#endif // __DEFS_H
