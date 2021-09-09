![PROJECT_PHOTO](https://github.com/AlexGyver/BluetoothCar/blob/master/proj_img.jpg)
# Bluetooth машинка на Arduino своими руками
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Как скачать и прошить](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)
[![AlexGyver YouTube](http://alexgyver.ru/git_banner.jpg)](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)

<a id="chapter-0"></a>
## Описание проекта
Bluetooth машинка с FPV камерой под управлением Arduino
Особенности:
- Управление со смартфона по Bluetooth
- Трансляция видео на смартфон
- Полный привод! =) 4х4 блэт
- Подробности в видео: https://youtu.be/X99RF7amJgY
<a id="chapter-1"></a>
## Папки
**ВНИМАНИЕ! Если это твой первый опыт работы с Arduino, читай [инструкцию](#chapter-4)**
- **libraries** - библиотеки проекта. Заменить имеющиеся версии
- **firmware** - прошивки
- **schemes** - схемы подключения
- **Android** - все файлы с примерами для Android и Thunkable

<a id="chapter-2"></a>
## Схемы
![SCHEME](https://github.com/AlexGyver/BluetoothCar/blob/master/schemes/scheme.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
### Ссылки оставлены на магазины, с которых я закупаюсь уже не один год
* Powerbank XiaoMI USBx2 https://ali.ski/oyIjw
* Arduino NANO 328p – искать
* https://ali.ski/-uT7S
* https://ali.ski/PLNYn
* https://ali.ski/ucMgYS
* https://ali.ski/cYeBTg
* Giant4 (Россия)
* Bluetooth HC-06 – искать
* https://ali.ski/91R8Qh
* https://ali.ski/DcM7b
* Драйвер – искать
* https://ali.ski/0jheQ
* https://ali.ski/tAwOBN
* https://ali.ski/VNa8d
* Моторчик и колесо
* https://ali.ski/feqKe  
* https://ali.ski/7NehCQ
* 4 мотора и колёса https://ali.ski/7zquNl
* Макетка https://ali.ski/OHsnx
* Провода для макетки https://ali.ski/TPKJ0U
* Танковое шасси https://ali.ski/BV2Th
* FPV:
* Камера 3 в 1
* https://ali.ski/WjRxwm  
* https://ali.ski/R41wV3
* FPV OTG приёмник
* https://ali.ski/GhddD 
* https://ali.ski/P9R4AN
* Другие варианты приёма видео:
* FPV часы https://ali.ski/q30nC
* Крутой дисплей https://ali.ski/7bk8ZH
* FPV шлем как у меня https://ali.ski/yHh4Kx
* Хороший FPV шлем https://ali.ski/Shcb2S
* FPV очки https://ali.ski/F5eqnV

## Вам скорее всего пригодится
* [Всё для пайки (паяльники и примочки)](http://alexgyver.ru/all-for-soldering/)
* [Недорогие инструменты](http://alexgyver.ru/my_instruments/)
* [Все существующие модули и сенсоры Arduino](http://alexgyver.ru/arduino_shop/)
* [Электронные компоненты](http://alexgyver.ru/electronics/)
* [Аккумуляторы и зарядные модули](http://alexgyver.ru/18650/)

<a id="chapter-4"></a>
## Как скачать и прошить
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Ардуино, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* Установить библиотеки в  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86)
* **Подключить внешнее питание 5 Вольт**
* Подключить Ардуино к компьютеру
* Запустить файл прошивки (который имеет расширение .ino)
* Настроить IDE (COM порт, модель Arduino, как в статье выше)
* Настроить что нужно по проекту
* Нажать загрузить
* Пользоваться  

## Настройки в коде
    MOTOR_MAX 255	// максимальный сигнал на мотор (max 255)
    JOY_MAX 40   	// рабочий ход джойстика (из приложения)
	
<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта?  
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы?  
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Вылетает ошибка загрузки / компиляции!
О: Читай тут: https://alexgyver.ru/arduino-first/#step-5

В: Сколько стоит?  
О: Ничего не продаю.

### Вопросы по этому проекту

<a id="chapter-6"></a>
## Полезная информация
* [Мой сайт](http://alexgyver.ru/)
* [Основной YouTube канал](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
* [YouTube канал про Arduino](https://www.youtube.com/channel/UC4axiS76D784-ofoTdo5zOA?sub_confirmation=1)
* [Мои видеоуроки по пайке](https://www.youtube.com/playlist?list=PLOT_HeyBraBuMIwfSYu7kCKXxQGsUKcqR)
* [Мои видеоуроки по Arduino](http://alexgyver.ru/arduino_lessons/)
