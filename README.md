# iKrypt
Прошивка для первой версии управляющей платы скрытого домашнего хранилища "iKrypt"

В этом репозитории вы можете найти source код старой версии прошивки (новая будет доступна позже, пишется на SPL + FreeRTOS [ESP-IDF]), а также 
скриншоты из Altium Designer с 2D и 3D видами старой и новой версий платы управления, и скриншоты мобильного приложения.
Движение отсеков реализовано с помощью шаговых моторов и различных кинематических систем. Управление происходит через мобильное приложение по Bluetooth либо Wi-Fi.

Разработка платы ведется в Altium Designer 20. Старая версия платы была Arduino-shield'ом для Arduino Mega 2560. В новой версии
МК разведены на плате (а это AT32F403 и ESP32). На борту поддержка Bluetooth/Wi-Fi, RFID, управление несколькими шаговыми двигателями (DIR/STEP драйвера внешние),
также управление подсветкой (адресная светодиодная лента) и спящий режим.
Размеры платы были определены инженером-конструктором.

Новая версия платы:
![1_ikrypt_v2](images/ikrypt2dview.jpg)

![2_ikrypt_v2](images/ikrypt3dview.jpg)

Скриншоты приложения:

![1_app](images/1.jpg)
![2_app](images/2.jpg)
![3_app](images/3.jpg)
![4_app](images/4.jpg)

Старая версия платы:

![1_ikrypt](https://github.com/flensimdotcore/iKrypt/assets/62958741/397a641d-efee-49ae-a721-f0f49553506d)

![2_ikrypt](https://github.com/flensimdotcore/iKrypt/assets/62958741/fa0e22dc-371d-4ef3-915c-5e01a0a38e01)

![3_ikrypt](https://github.com/flensimdotcore/iKrypt/assets/62958741/dcc56542-4f33-42ec-ae20-cf5d935bdf70)
