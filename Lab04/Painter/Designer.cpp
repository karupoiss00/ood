#include "Designer.h"
#include "PictureDraft.h"
#include "IShapeFactory.h"

using namespace std;

CDesigner::CDesigner(IShapeFactory& factory)
	:m_factory(factory)
{
}


CDesigner::~CDesigner()
{
}

CPictureDraft CDesigner::CreateDraft(std::istream& inputData)
{
	CPictureDraft draft;
	string line;

	while (getline(inputData, line))
	{
		try
		{
			draft.AddShape(m_factory.CreateShape(line));
		}
		catch (exception const& e) 
		{
			cout << e.what() << endl;
		}
	}

	return draft;
}
