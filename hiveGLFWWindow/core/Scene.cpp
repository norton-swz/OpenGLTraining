#include "Scene.h"

namespace hiveWindow
{
	CScene::CScene() :m_pRootNode(std::make_shared<CNode>("ROOT")), m_pCamera(nullptr), m_pLight(nullptr)
	{
	}
}