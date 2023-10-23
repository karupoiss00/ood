#include "FunctionalCommand.h"

using namespace std;

FunctionalCommand::FunctionalCommand(const function<void()>& doExecute, const function<void()>& doUnexecute)
	: m_doExecute(doExecute)
	, m_doUnexecute(doUnexecute)
{
}

void FunctionalCommand::DoExecute()
{
	m_doExecute();
}

void FunctionalCommand::DoUnexecute()
{
	m_doUnexecute();
}
