/*
 * Copyright (C) 2006-2010 - Frictional Games
 *
 * This file is part of HPL1 Engine.
 *
 * HPL1 Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HPL1 Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HPL1 Engine.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "impl/SqScript.h"
#include "system/LowLevelSystem.h"
#include "system/String.h"
#include "math/Math.h"
#include "impl/Platform.h"
#include <stdio.h>

#include "scripthelper/scripthelper.h"

namespace hpl {

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cSqScript::cSqScript(const tString& asName,asIScriptEngine *apScriptEngine,
							cScriptOutput *apScriptOutput, int alHandle)
		: iScript(asName)
	{
		mpScriptEngine = apScriptEngine;
		mpScriptOutput = apScriptOutput;
		mlHandle = alHandle;

		mpContext = mpScriptEngine->CreateContext();

		//Create a unique module name
		msModuleName = "Module_"+cString::ToString(cMath::RandRectl(0,1000000))+
						"_"+cString::ToString(mlHandle);

	}

	cSqScript::~cSqScript()
	{
		if (mpModule) mpModule->Discard();
		mpContext->Release();
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	bool cSqScript::CreateFromFile(const tString& asFileName)
	{
		int lLength;
		char *pCharBuffer = LoadCharBuffer(asFileName,lLength);
		if(pCharBuffer==NULL){
			Error("Couldn't load script '%s'!\n",asFileName.c_str());
			return false;
		}
		//angelscript new api usage from scummvm's code--get a module from engine instead
		// of calling directly from engine
		mpModule = mpScriptEngine->GetModule(msModuleName.c_str(), asGM_ALWAYS_CREATE);
		if (mpModule->AddScriptSection(msModuleName.c_str(), pCharBuffer, lLength) < 0) {
			Error("Couldn't add script '%s'!\n", asFileName.c_str());
			hplDeleteArray(pCharBuffer);
			return false;
		}

		if(mpModule->Build()<0)
		{
			Error("Couldn't build script '%s'!\n",asFileName.c_str());
			Log("------- SCRIPT OUTPUT BEGIN --------------------------\n");
			mpScriptOutput->Display();
			mpScriptOutput->Clear();
			Log("------- SCRIPT OUTPUT END ----------------------------\n");



			hplDeleteArray(pCharBuffer);
			return false;
		}
		mpScriptOutput->Clear();

		hplDeleteArray(pCharBuffer);
		return true;
	}

	//-----------------------------------------------------------------------

	int cSqScript::GetFuncHandle(const tString& asFunc)
	{
		if (mpModule == nullptr) { return -1; }
		asIScriptFunction *script =
			mpModule->GetFunctionByName(asFunc.c_str());
		return script ? script->GetId() : -1;
	}

	//-----------------------------------------------------------------------

	void cSqScript::AddArg(const tString& asArg)
	{

	}

	//-----------------------------------------------------------------------

	bool cSqScript::Run(const tString& asFuncLine)
	{
		if (mpModule == nullptr){ return false;}
		return ExecuteString(mpScriptEngine, asFuncLine.c_str(), mpModule);
	}

	//-----------------------------------------------------------------------

	bool cSqScript::Run(int alHandle)
	{
		auto script = mpScriptEngine->GetFunctionById(alHandle);
		if (script == nullptr){ return false; }
		if (mpContext->Prepare(script) < 0) return false;

		/* Set all the args here */

		return mpContext->Execute() == asEXECUTION_FINISHED;
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PRIVATE METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	char* cSqScript::LoadCharBuffer(const tString& asFileName, int& alLength)
	{
		FILE *pFile = fopen(asFileName.c_str(), "rb");
		if(pFile==NULL){
			return NULL;
		}

		int lLength = (int)Platform::FileLength(pFile);
		alLength = lLength;

		char *pBuffer = hplNewArray(char,lLength);
		fread(pBuffer, lLength, 1, pFile);

		fclose(pFile);

		return pBuffer;
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// STATIC PRIVATE METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------

}
