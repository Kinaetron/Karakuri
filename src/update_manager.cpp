#include <algorithm>
#include "update_manager.h"

std::vector<UpdateComponent*> UpdateManager::updateComponents;

void UpdateManager::Add(UpdateComponent* component) {
	updateComponents.push_back(component);
}

void UpdateManager::Remove(UpdateComponent* component) 
{
	auto elementFound = std::find(
		updateComponents.begin(), 
		updateComponents.end(), 
		component);

	if (elementFound != updateComponents.end()) {
		updateComponents.erase(elementFound);
	}
}

const std::vector<UpdateComponent*> UpdateManager::UpdateComponents() {
	return updateComponents;
}
