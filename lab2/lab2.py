import random
from enum import Enum
from tabulate import tabulate


class AccessRights(str, Enum):
    DENY = "Запрет"
    READ = "Чтение"
    WRITE = "Запись"
    GRANT = "Передача прав"
    FULL_ACCESS = "Полные права"


class DiscretionarySecurityPolicyModule:
    def __init__(self, users_count: int, objects_count: int):
        self.user_id = None
        self.users_count = users_count
        self.objects_count = objects_count
        self.access_matrix = self.generate_access_matrix()
        self.users = self.generate_users_matrix()

    @property
    def user_index(self):
        return self.users.index(user_id)

    def read(self, object_num: int):
        if (
            AccessRights.READ in self.access_matrix[self.user_index][object_num]
            or AccessRights.FULL_ACCESS
            in self.access_matrix[self.user_index][object_num]
        ):
            print("Операция прошла успешно")
        else:
            print(
                "Отказ в выполнении операции. У Вас нет прав на чтение для данного объекта"
            )

    def write(self, object_num: int):
        if (
            AccessRights.WRITE in self.access_matrix[self.user_index][object_num]
            or AccessRights.FULL_ACCESS
            in self.access_matrix[self.user_index][object_num]
        ):
            print("Операция прошла успешно")
        else:
            print(
                "Отказ в выполнении операции. У Вас нет прав на запись для данного объекта"
            )

    def grant(self, object_num: int):
        if (
            AccessRights.GRANT in self.access_matrix[self.user_index][object_num]
            or AccessRights.FULL_ACCESS
            in self.access_matrix[self.user_index][object_num]
        ):
            user_index_to_grant = int(
                input("Право передается пользователю. Укажите его номер: ")
            ) - 1
            rights_to_grant_str = input(
                "Введите права, которые вы хотите передать пользователю (через запятую): "
            ).split(",")
            rights_to_grant = []
            for right_str in rights_to_grant_str:
                try:
                    right = AccessRights(right_str.strip())
                    rights_to_grant.append(right)
                except ValueError:
                    print(f"{right_str.strip()} is not a valid AccessRights. Skipping.")
            success = self.__modify_rights(user_index_to_grant, object_num, rights_to_grant)
            if success:
                self.print_access_matrix()
        else:
            print(
                "Отказ в выполнении операции. У Вас нет прав на передачу прав для данного объекта"
            )

    def __modify_rights(
        self, user_index_to_grant: int, object_num: int, rights_to_grant: list
    ) -> bool:
        # Проверяем, если передаются полные права
        if AccessRights.FULL_ACCESS in rights_to_grant:
            print("Ошибка: Передавать полные права нельзя.")
            return False

        if AccessRights.GRANT in rights_to_grant:
            print("Ошибка: Передавать права на передачу прав нельзя.")
            return False

        # Добавляем новые права к существующим
        current_rights = self.access_matrix[user_index_to_grant][object_num]
        new_rights = list(set(current_rights + rights_to_grant))
        self.access_matrix[user_index_to_grant][object_num] = new_rights
        return True

    def generate_access_matrix(self):
        # Матрица доступа
        access_matrix = [
            [AccessRights.DENY] * self.objects_count for _ in range(self.users_count)
        ]

        # Установка полных прав для администратора (первый пользователь)
        admin_index = 0
        for i in range(self.objects_count):
            access_matrix[admin_index][i] = AccessRights.FULL_ACCESS

        # Заполнение матрицы доступа случайными правами для остальных пользователей
        for i in range(self.users_count):
            if i != admin_index:
                for j in range(self.objects_count):
                    # Выбираем случайные права из доступных, за исключением "Полных прав"
                    random_rights = random.sample(
                        [AccessRights.READ, AccessRights.WRITE],
                        k=random.randint(0, 2),
                    )
                    access_matrix[i][j] = random_rights

        return access_matrix

    def generate_users_matrix(self):
        arr = [f"Пользователь {i - 1}" for i in range(1, self.users_count + 1)]
        arr[0] = "Admin"
        return arr

    def login(self, user_id: str):
        if user_id in self.users:
            self.user_id = user_id
            print(
                f"Идентификация прошла успешно, добро пожаловать в систему, {user_id}"
            )
            print("Перечень Ваших прав:")
            for i in range(self.objects_count):
                access_rights_list = (
                    self.access_matrix[self.user_index][i].value
                    if isinstance(self.access_matrix[self.user_index][i], AccessRights)
                    else ", ".join(self.access_matrix[self.user_index][i])
                )
                print(f"Объект{i + 1}: {access_rights_list}")
            while True:
                action = input("Жду ваших указаний > ").strip().lower()
                match action:
                    case "quit":
                        print(f"Работа пользователя {user_id} завершена. До свидания.")
                        break
                    case "read":
                        object_num = (
                            int(input("Над каким объектом производится операция? ")) - 1
                        )
                        self.read(object_num)
                    case "write":
                        object_num = (
                            int(input("Над каким объектом производится операция? ")) - 1
                        )
                        self.write(object_num)
                    case "grant":
                        try:
                            object_num = (
                                    int(input("Право на какой объект передается? ")) - 1
                            )
                            self.grant(object_num)
                        except Exception:
                            print("Неверная команда.")
                            pass
                    case _:
                        print("Неверная команда.")
        else:
            print("Ошибка входа. Пользователь не найден.")

    def print_access_matrix(self):
        # Формирование списка списков для tabulate
        matrix_to_show = [
            [
                j.value if isinstance(j, AccessRights) else [l.value for l in j] if len(j) > 0 else AccessRights.DENY.value
                for j in i
            ]
            for i in self.access_matrix
        ]

        matrix_with_users = [
            [user] + row for user, row in zip(self.users, matrix_to_show)
        ]
        # Вывод матрицы доступа с именами пользователей слева
        print(
            tabulate(
                matrix_with_users,
                headers=["Пользователь / Объект"]
                + [f"Объект {i}" for i in range(1, self.objects_count + 1)],
                tablefmt="pretty",
            )
        )


if __name__ == "__main__":
    module = DiscretionarySecurityPolicyModule(users_count=4, objects_count=4)
    module.print_access_matrix()
    user_id = input("Введите идентификатор пользователя: ")
    module.login(user_id)
