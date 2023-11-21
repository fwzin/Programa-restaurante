class Produto:
    def __init__(self, nome, preco):
        self.nome = nome
        self.preco = preco


def calcular_valor_total(produtos, cobrar_garcom):
    valor_total = sum(produto.preco for produto in produtos)

    if cobrar_garcom:
        valor_total *= 1.15  # Cobrar 15% a mais se o garçom for incluído

    return valor_total


def obter_confirmacao():
    confirmacao = input("Confirmar o pedido (S para sim, N para não): ")
    return confirmacao.upper() == 'S'


def mostrar_menu():
    print("\nMenu:")
    print("a. Prato Principal")
    print("b. Bebida")
    print("c. Sobremesa")
    print("x. Finalizar Pedido")
    escolha = input("Escolha uma opção: ")
    return escolha.lower()


def adicionar_produto(produtos):
    print()
    nome = input("Digite o nome do produto: ")
    preco = float(input("Digite o preço do produto: "))
    produtos.append(Produto(nome, preco))


def main():
    print("\033[32mBem-vindo ao Restaurante Cantinho de Santana!\033[0m")

    funcionario = input("Digite o nome do funcionário: ")

    produtos = []
    cobrar_garcom = False

    escolha = ''
    while escolha != 'x' and len(produtos) < 50:
        escolha = mostrar_menu()

        if escolha == 'a' or escolha == 'b' or escolha == 'c':
            adicionar_produto(produtos)
        elif escolha != 'x':
            print("\033[31mOpção inválida. Tente novamente.\033[0m")

    cobrar_garcom_resposta = input("Deseja cobrar os 15% do garçom (S para sim, N para não): ")
    cobrar_garcom = cobrar_garcom_resposta.upper() == 'S'

    valor_total = calcular_valor_total(produtos, cobrar_garcom)

    from datetime import datetime

    data_hora = datetime.now().strftime("%d/%m/%Y %H:%M:%S")

    print("\nResumo do Pedido:")
    for produto in produtos:
        print(f"Produto: {produto.nome} - R$ {produto.preco:.2f}")
    print(f"Cobrar Garçom: {'Sim' if cobrar_garcom else 'Não'}")
    print(f"Valor Total do Pedido: R$ {valor_total:.2f}")

    if obter_confirmacao():
        with open("recibo.txt", "a") as recibo_arquivo:
            recibo_arquivo.write("Recibo do Pedido:\n")
            recibo_arquivo.write(f"Data e Hora do Pedido: {data_hora}\n")
            recibo_arquivo.write(f"Funcionário: {funcionario}\n")

            for produto in produtos:
                recibo_arquivo.write(f"Produto: {produto.nome} - R$ {produto.preco:.2f}\n")

            recibo_arquivo.write(f"Cobrar Garçom: {'Sim' if cobrar_garcom else 'Não'}\n")
            recibo_arquivo.write(f"Valor Total do Pedido: R$ {valor_total:.2f}\n")
            recibo_arquivo.write("Pedido registrado com sucesso. Obrigado!\n\n")

        print("Recibo do pedido salvo em 'recibo.txt'.")
    else:
        print("Pedido cancelado.")

    nova_compra = input("Deseja fazer outro pedido (S para sim, N para não): ")
    if nova_compra.upper() != 'S':
        print("Finalizando programa.")


if __name__ == "__main__":
    main()
