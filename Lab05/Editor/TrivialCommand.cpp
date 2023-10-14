#include "TrivialCommand.h"

using namespace std;

TrivialCommand::TrivialCommand(const function<void()>& doExecute, const function<void()>& doUnexecute)
	: m_doExecute(doExecute)
	, m_doUnexecute(doUnexecute)
{
}

void TrivialCommand::DoExecute()
{
	m_doExecute();
}

void TrivialCommand::DoUnexecute()
{
	m_doUnexecute();
}
