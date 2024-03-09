import platform
import winreg
import psutil

def get_cpu_frequency():
    return psutil.cpu_freq().current / 1000

cpu_frequency = get_cpu_frequency()
print("Частота процессора:", cpu_frequency, "ГГц")


def get_unique_computer_identifier():
    try:
        windows_info = platform.uname()
        print("OS: " + windows_info.system)
        return windows_info.system
    except Exception as e:
        return None

def get_registry_value(key_path, value_name):
    try:
        # Открываем ключ реестра
        key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, key_path)
        # Получаем значение по имени
        value, _ = winreg.QueryValueEx(key, value_name)
        # Закрываем ключ
        winreg.CloseKey(key)
        return value
    except FileNotFoundError:
        print("Указанный путь в реестре не найден.")
    except Exception as e:
        print("Ошибка при чтении значения из реестра:", e)
    return None

def check_computer_identity():
    gz = get_cpu_frequency()
    ghz = get_registry_value(r"HARDWARE\DESCRIPTION\System\CentralProcessor\0", "~MHz")
    if ghz == 2371 and gz == 3.375:
        print("Программа запущена на ожидаемом компьютере.")
    else:
        print("Программа запущена на неподдерживаемом компьютере.")


if __name__ == "__main__":
    check_computer_identity()