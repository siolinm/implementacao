Todo
===

- [x] Documentação
- [x] Adicionar EPS em operações que envolvem tempo e distância (falta splay_tree.c)
- [x] Desempate de eventos na fila de prioridade: DOWN -> HORIZONTAL -> UP
    - [x] checar
- [x] Desenhar lcandp na tela
- [x] Adicionar desenhos de debug para os eventos (com textos)

Bugs
===

- [x] Bugs nos cones em casos degenerados (pontos muito próximos) h/h1.in, r/r1.in
- [x] No torneio em d/h0.in: par p -- c é duplicado em algum momento. Provável erro em: insertTourn ou deleteTourn. Motivo: certificados de pares deletados no torneio não eram deletados, bem como certificados de pares inseridos.
- [x] Em d/h1.in os cones up estão completamente errados. Erro: no instante 0 p pertence a Cands(a) mas na lista p está à esquerda de a, como p continua se movendo para esquerda, uma troca horizontal não é chamada e as estruturas não são atualizadas.
  - [x] Solução: forçar eventos quando os pontos empatam. (comentar na reunião)

Testes
====

Horizontal
---

- [x] tests/h/h0.in
- [ ] tests/h/h1.in
- [ ] tests/h/d0.in
- [ ] tests/h/d1.in
- [ ] tests/h/u0.in
- [ ] tests/h/u1.in

Down
---

- [ ] tests/d/h0.in
- [ ] tests/d/h1.in
- [ ] tests/d/d0.in
- [ ] tests/d/d1.in
- [ ] tests/d/u0.in
- [ ] tests/d/u1.in

Up
---

- [ ] tests/u/h0.in
- [ ] tests/u/h1.in
- [ ] tests/u/d0.in
- [ ] tests/u/d1.in
- [ ] tests/u/u0.in
- [ ] tests/u/u1.in

Random
---

- [ ] tests/r/r0.in
- [ ] tests/r/r1.in