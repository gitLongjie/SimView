#define OSGRENDER_DLL
#include <windows.h>
#include <osgViewer/View>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osg/GraphicsContext>
#include "../Public/Kerner/Kerner.h"
#include "../Public/OsgRender/OsgRender.h"
#include "../Public/OsgRender/IOsgViewConfig.h"
#include "OsgView.h"

namespace SimView
{
	// ���캯��
	COsgView::COsgView(IOsgViewConfig* pIConfig)
		:m_pGroup(NULL),m_pView(new osgViewer::View), m_pIConfig(pIConfig)
	{
		// ��������
		m_pView->setName(pIConfig->GetName());
	}

	// ��������
	COsgView::~COsgView()
	{
		// �Ƴ���Ⱦ��
		if (NULL == m_pGroup)
		{
			return;
		}
		m_pGroup->removeChildren(0, m_pGroup->getNumChildren());
	}

	// ��ʼ��������
	void COsgView::InitManipulator(void)
	{
		// ������ͼ
		m_pKeyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
		m_pIConfig->InitManipulator(m_pKeyswitchManipulator);
	}

	// ��ʼ�����
	void COsgView::InitCamera(void)
	{
		// ����������
		osg::GraphicsContext::Traits* pTraits = new osg::GraphicsContext::Traits;
		// �������ú�������ʹ��������ز���
		m_pIConfig->InitContextTraits(pTraits);

		// �������������
		osg::GraphicsContext* pGc = osg::GraphicsContext::createGraphicsContext(pTraits);
		// ��ʼ�����
		osg::Camera* pCamera = m_pView->getCamera();
		// ����������
		pCamera->setGraphicsContext(pGc);
		// ������ͼ
		pCamera->setViewport(new osg::Viewport(pTraits->x, pTraits->y, pTraits->width, pTraits->height));
		// ����ͶӰ
		pCamera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		pCamera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
		pCamera->setProjectionMatrixAsPerspective(
			30.0f, static_cast<double>(pTraits->width) / static_cast<double>(pTraits->height), 0.1, 1000.0);
		m_pView->setCamera(pCamera);
		// ���Ӳ�����
		m_pView->setCameraManipulator(m_pKeyswitchManipulator);

		m_pGroup = new osg::Group;
	}

	// �������
	SVString COsgView::GetName(void) const
	{
		return (m_pIConfig->GetName());
	}

	// �����ͼ
	osgViewer::View* COsgView::GetView(void) const
	{
		return (m_pView);
	}

	// ���ӽڵ�
	void COsgView::AddRenderObj(void* pRenderObj)
	{
		// ת����osg�ڵ�
		osg::Node* pNode = static_cast<osg::Node*>(pRenderObj);
		if (NULL == pNode)
		{
			SIMVIEW_EXCEPT(CSVExpection::ERR_CONVERT_FAILD, "����ת��ʧ��", "AddRenderObj");
		}

		// �ж��Ƿ�Ϊ��һ��
		int nCount = m_pGroup->getNumChildren();
		if (0 >= nCount)
		{
			m_pGroup->addChild(pNode);
			m_pView->setSceneData(m_pGroup);
			m_pView->setCameraManipulator(m_pKeyswitchManipulator);
		}
		else
		{
			m_pGroup->addChild(pNode);
		}
		ILogManage::GetSingleton().RecordLog("������Ⱦ�ڵ�ɹ�");
	}

	// 
}