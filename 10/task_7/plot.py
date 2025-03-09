import matplotlib.pyplot as plt
import os

# Данные
data = {
    "NumStrs": [1000000, 1100000, 1200000, 1300000, 1400000, 1500000, 1600000, 1700000, 1800000, 1900000],
    "RSHash": [118, 142, 173, 200, 243, 288, 319, 355, 396, 436],
    "JSHash": [110, 144, 158, 203, 239, 270, 302, 334, 392, 447],
    "PJWHash": [2401, 2902, 3462, 4078, 4760, 5486, 6333, 7088, 7955, 8841],
    "ELFHash": [2401, 2902, 3462, 4078, 4760, 5486, 6333, 7088, 7955, 8841],
    "BKDRHash": [129, 146, 169, 198, 227, 262, 298, 342, 386, 431],
    "SDBMHash": [144, 165, 188, 215, 243, 268, 304, 339, 379, 420],
    "DJBHash": [111, 137, 165, 197, 227, 273, 298, 342, 380, 416],
    "DEKHash": [217, 264, 304, 355, 425, 488, 548, 618, 690, 748],
    "APHash": [132, 159, 181, 210, 251, 281, 314, 363, 396, 432],
}

# Построение графиков
plt.figure(figsize=(12, 8))

for hash_func in data.keys():
    if hash_func != "NumStrs":
        plt.plot(data["NumStrs"], data[hash_func], label=hash_func)

# Настройка графика
plt.title("Зависимость коллизий от количества строк для разных хэш-функций (логарифмическая шкала)")
plt.xlabel("Количество строк")
plt.ylabel("Количество коллизий (логарифмическая шкала)")
plt.yscale('log')  # Логарифмическая шкала по оси Y
plt.grid(True, which="both", ls="--")  # Сетка для логарифмической шкалы
plt.legend()

# Сохранение графика в текущую папку
output_filename = "hash_collisions_plot_log_scale.png"
output_path = os.path.join(os.getcwd(), output_filename)
plt.savefig(output_path)

print(f"График сохранен в файл: {output_path}")

# Закрытие графика (опционально)
plt.close()