#pragma once
template<typename T_TYPE>
bool prefixMatch(T_TYPE prefix, T_TYPE objective){
	if(prefix.size() > objective.size()){
		return false;
	}

	bool found = true;

	for(int i = 0; i < prefix.size(); i++){
		if(prefix[i] != objective[i]){
			found = false;
			break;
		}
	}

	return found;
}

template<typename T_TYPE>
bool suffixMatch(T_TYPE suffix, T_TYPE objective){
	if(suffix.size() > objective.size()){
		return false;
	}

	bool found = true;

	int len = objective.size();
	for(int i = 1; i <= suffix.size(); i++){
		if(suffix[len -i] != objective[len -i]){
			found = false;
			break;
		}
	}

	return found;
}

