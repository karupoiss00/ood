#pragma once
#include <functional>
#include "AbstractCommand.h"

// переименовать в FunctionalCommand
class FunctionalCommand : public CAbstractCommand
{
public:
	FunctionalCommand(const std::function<void()>& doExecute, const std::function<void()>& doUnexecute);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	const std::function<void()> m_doExecute;
	const std::function<void()> m_doUnexecute;
};