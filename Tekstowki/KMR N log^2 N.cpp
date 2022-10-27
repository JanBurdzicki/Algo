	id = 27;

	for (int j=0; j<l; j++)
		KMR[j][0] = slowa[j] - 'a';


		cin >> slowa;

	for (int logi = 1; logi <= LOG; logi++){
		pary.clear();
		mapka.clear();

		for (int j = 0; j + (1 << logi) <= l; j++)  // update kmr
		pary.push_back({KMR[j][logi-1], KMR[j + (1 << (logi - 1))][logi - 1]});

		sort(pary.begin(), pary.end());

		for (auto para : pary){
			if (mapka.find(para) == mapka.end()){
				mapka[para] = id;
				id++;
			}
		}

		for (int j = 0; j + (1 << logi) <= l; j++)  // update kmr
		KMR[j][logi] = mapka[{KMR[j][logi-1], KMR[j + (1 << (logi - 1))][logi - 1]}];
	}