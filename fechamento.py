def calcular_total_do_dia():
    total_do_dia = 0.0

    try:
        with open("recibo.txt", "r") as recibo_arquivo:
            for linha in recibo_arquivo:
                valor_do_recibo = 0.0
                if "Valor Total do Pedido: R$" in linha:
                    valor_do_recibo = float(linha.split("R$")[1])
                    total_do_dia += valor_do_recibo
    except FileNotFoundError:
        print("Nenhum recibo encontrado. O restaurante não fez vendas hoje.")
        return None

    return total_do_dia


def main():
    total_do_dia = calcular_total_do_dia()

    if total_do_dia is not None:
        print(f"Total do dia: R$ {total_do_dia:.2f}")


if __name__ == "__main__":
    main()
