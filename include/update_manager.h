#ifndef UPDATE_MANAGER_H
#define UPDATE_MANAGER_H

#include <vector>
#include "update_component.h"

class UpdateManager
{
public:
	UpdateManager(const UpdateManager& that) = delete;
	UpdateManager(UpdateManager&& that) = delete;
	UpdateManager& operator=(const UpdateManager& rhs) = delete;
	UpdateManager& operator=(UpdateManager&& rhs) = delete;
	UpdateManager() = delete;

	static void Add(UpdateComponent* component);
	static void Remove(UpdateComponent* component);
	static const std::vector<UpdateComponent*> UpdateComponents();

private:
	static std::vector<UpdateComponent*> updateComponents;
};

#endif // !INPUT_MANAGER_H