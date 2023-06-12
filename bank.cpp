#include <stdio.h>
int m[8], v[1000], ans = 0;

int unit[8] = { 50000,10000,5000,1000,500,100,50,10 };

void save(int money[8]) {
	for (register int i = 0; i < 8; i++) {
		m[i] = money[i];
	}
	for (register int i = 0; i < 1000; i++) {
		v[i] = 0;
	}
	ans = 0;
}

int calc(int account[1000], int result[1000][8], double weight[8]) {
	register int i, j, k, l, min_i, x, c, cnt = 0, _m[8];
	register double value, min;

	for (i = 0; i < 8; i++)
		_m[i] = m[i];

	for (i = 0; i < 1000; i++) {
		min = 99999999;
		min_i = -1;

		for (j = 0; j < 1000; j++) {
			if (v[j]) continue;
			value = 0;
			x = account[j];

			for (k = 0; k < 8; k++) {
				l = ((x / unit[k]) > _m[k]) ? _m[k] : (x / unit[k]);
				x -= unit[k] * l;

				if (_m[k] != 0) {
					value += weight[k] * l / _m[k];
				}
			}

			if (x != 0) {
				v[j] = 1; 
				continue;
			}

			if (value < min) {
				min = value;
				min_i = j;
			}
		}

		if (min_i == -1) break;
		cnt++;
		v[min_i] = 1;
		x = account[min_i];
		for (int k = 0; k < 8; k++) {
			l = ((x / unit[k]) > _m[k]) ? _m[k] : (x / unit[k]);
			result[min_i][k] = l;
			x -= unit[k] * l;
			_m[k] -= l;
		}
	}

	return cnt;
}

int calc2(int account[1000], int result[1000][8], double weight[8]) {
	register int i, j, k, l, min_i, x, c, cnt = 0, _m[8];
	register double value, min;

	for (i = 0; i < 8; i++)
		_m[i] = m[i];

	for (i = 0; i < 1000; i++) {
		x = account[i];
		for (int k = 0; k < 8; k++) {
			l = ((x / unit[k]) > _m[k]) ? _m[k] : (x / unit[k]);
			x -= unit[k] * l;
		}

		if (x != 0) continue;
		cnt++;
		x = account[i];
		for (int k = 0; k < 8; k++) {
			l = ((x / unit[k]) > _m[k]) ? _m[k] : (x / unit[k]);
			result[i][k] = l;
			x -= unit[k] * l;
			_m[k] -= l;
		}
	}
	return cnt;
}

int calc3(int account[1000], int result[1000][8], double weight[8]) {
	register int i, j, k, l, min_i, x, c, cnt = 0, _m[8];
	register double value, min;

	for (i = 0; i < 8; i++)
		_m[i] = m[i];

	for (i = 0; i < 1000; i++) {
		min = 99999999;
		min_i = -1;

		for (j = 0; j < 1000; j++) {
			if (v[j]) continue;
			value = 0;
			x = account[j];

			for (k = 0; k < 8; k++) {
				l = ((x / unit[k]) > _m[k]) ? _m[k] : (x / unit[k]);
				x -= unit[k] * l;

				if (_m[k] != 0) value += weight[k] * l / m[k];
			}

			if (x != 0) {

				v[j] = 1;
				continue;
			}

			if (value < min) {
				min = value;
				min_i = j;
			}
		}

		if (min_i == -1) break;
		cnt++;
		v[min_i] = 1;
		x = account[min_i];
		for (int k = 0; k < 8; k++) {
			l = ((x / unit[k]) > _m[k]) ? _m[k] : (x / unit[k]);
			result[min_i][k] = l;
			x -= unit[k] * l;
			_m[k] -= l;
		}
	}

	return cnt;
}



void withdraw(int account[1000], int result[1000][8]) {
	for (register int i = 0; i < 1000; i++) {
		for (register int j = 0; j < 8; j++) 
		{
			result[i][j] = 0;
		}
		v[i] = 0;
	}
	double weight[8] = {0,1,0.5,1,0.5,1,0.5,3};
	int cnt3 = calc3(account, result, weight);
	for (register int i = 0; i < 1000; i++) {
		for (register int j = 0; j < 8; j++) {
			result[i][j] = 0;
		}
		v[i] = 0;
	}
	/*int cnt2 = calc2(account, result, weight);
	for (register int i = 0; i < 1000; i++) {
		for (register int j = 0; j < 8; j++) {
			result[i][j] = 0;
		}
		v[i] = 0;
	}*/
	int cnt = calc(account, result, weight);
	
	if (cnt < cnt3) {
		for (register int i = 0; i < 1000; i++) {
			for (register int j = 0; j < 8; j++) {
				result[i][j] = 0;
			}
			v[i] = 0;
		}
		calc3(account, result, weight);
	}
}
