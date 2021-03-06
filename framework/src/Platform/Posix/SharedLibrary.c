// Copyright 2021 Fedir Melnichenko
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <Platform/SharedLibrary.h>

#include <dlfcn.h>

SharedLibrary SharedLibraryLoad(const char* name)
{
    return (SharedLibrary)dlopen(name, RTLD_LAZY);
}

void SharedLibraryFree(SharedLibrary library)
{
    dlclose((void*)library);
}

void* SharedLibraryGetSymbol(SharedLibrary library, const char* symbolName)
{
    return (void*)dlsym((void*)library, symbolName);
}