#include "pch.h"
#include "CComponent.h"

CComponent::CComponent(CObject* _pOwner)
	: m_pOwner(_pOwner)
{
}

CComponent::~CComponent()
{
}
