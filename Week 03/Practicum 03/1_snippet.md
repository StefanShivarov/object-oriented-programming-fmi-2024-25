**1.** В двоичен файл трябва да се запише масив от цели числа с размер 5. 
```c++
int main() {
	std::ofstream file("myFile.dat", std::ios::out | std::ios::binary);
	if (!file.is_open()) {
		return -1;
	}
	int arr[5] = { 1, 2, 3, 4, 5 };
}
```

Кои са всички **правилни начини**, по които да се запише arr във file.
```c++
- a) file.write((const char*)arr, sizeof(arr));
- b) file.write((char*)arr, sizeof(arr));
- c) file.write((const char*)arr, 5*sizeof(int));
- d) file.write((char*)arr, 5*sizeof(int));
- e) нито един от изброените варианти не е верен
```
