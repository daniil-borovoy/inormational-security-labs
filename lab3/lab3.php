<?php

function generate_password($alphabet, $length) {
    $password = "";
    $alphabetLength = strlen($alphabet);
    for ($i = 0; $i < $length; $i++) {
        $randomIndex = mt_rand(0, $alphabetLength - 1);
        $password .= $alphabet[$randomIndex];
    }
    return $password;
}

function find_length($S, $A) {
    $L = log($S, $A);
    $L = ceil($L);
    return $L;
}

function main($v, $t, $p_power) {
    $V = $v * 24 * 60 * 7;
    $T = $t / 7;
    $P = pow(10, -$p_power);

    // Выбираем алфавит
    $alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";

    // Вычисляем S
    $A = strlen($alphabet);
    $S = abs(($V * $T) / $P);

    $L = find_length($S, $A);
    $password = generate_password($alphabet, $L);
    echo "Сгенерированный пароль: $password\n";
    echo "Длина: $L\n";
}

$V = (int) readline("Введите V: ");
$T = (int) readline("Введите T: ");
$P = (int) readline("Введите степень P: ");
main($V, $T, $P);

?>
