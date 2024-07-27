numero Posicao = 0
numero Kp = 11.5
numero Kd = 1.5
numero VelocBase = 200
numero erroAnt = 0
numero erro = 0
numero quantPreto = 0
numero VelocAdj = 0
numero CorPreta = 110
numero ultimaPosicao = 0
numero loopobstaculo = 0
numero tempoInicio = 0
numero resgate = 0

tarefa MotorPID {
    erro = 0 - Posicao
    VelocAdj = erro*Kp + (erro-erroAnt) *Kd
    erroAnt = erro
    Motor("frmotor", VelocBase-VelocAdj)
    Motor("brmotor", VelocBase-VelocAdj)
    Motor("flmotor", VelocBase+VelocAdj)
    Motor("blmotor", VelocBase+VelocAdj)
}

tarefa AndarFrente() {
    Motor("frmotor", 200)
    Motor("brmotor", 200)
    Motor("flmotor", 200)
    Motor("blmotor", 200)
}

tarefa AndarAtras() {
    Motor("frmotor", 0-200)
    Motor("brmotor", 0-200)
    Motor("flmotor", 0-200)
    Motor("blmotor", 0-200)
}

tarefa CurvaCentro180 {
    Motor("frmotor", 200)
    Motor("brmotor", 200)
    Motor("flmotor", 0-200)
    Motor("blmotor", 0-200)
    Esperar(7030)
}

tarefa CurvaEsquerda90 {
    Motor("frmotor", 200)
    Motor("brmotor", 200)
    Motor("flmotor", 0-200)
    Motor("blmotor", 0-200)
    Esperar(3515)
}

tarefa CurvaDireita90 {
    Motor("frmotor", 0-200)
    Motor("brmotor", 0-200)
    Motor("flmotor", 200)
    Motor("blmotor", 200)
    Esperar(3515)
}

tarefa PosicaoRobo{
    numero ValorPosicao=0
    quantPreto=0
    se ( CorAzul("rc2") <= CorPreta  ) entao{
        ValorPosicao=ValorPosicao-100
        quantPreto=quantPreto+1
    }
    se ( CorAzul("rc1") <= CorPreta  ) entao{
        ValorPosicao=ValorPosicao-50
        quantPreto=quantPreto+1
    }
    se ( CorAzul("cc") <= CorPreta  ) entao{
        ValorPosicao=ValorPosicao+0
        quantPreto=quantPreto+1
    }
    se ( CorAzul("lc1") <= CorPreta  ) entao{
        ValorPosicao=ValorPosicao+50
        quantPreto=quantPreto+1
    }
    se ( CorAzul("lc2") <= CorPreta  ) entao{
        ValorPosicao=ValorPosicao+100
        quantPreto=quantPreto+1
    }
    se (quantPreto > 0) entao{
        Posicao=ValorPosicao/quantPreto        
    }

    se (quantPreto == 0) entao {
        Posicao=ultimaPosicao        
    }
    ultimaPosicao=Posicao    
}

tarefa CurvaVerde {
    se (CorVerde("rc1") > CorAzul("rc1") + CorVermelho("rc1") ou CorVerde("lc1") > CorAzul("lc1") + CorVermelho("lc1") ou CorVerde("rc2") > CorAzul("rc2") + CorVermelho("rc2") ou CorVerde("lc2") > CorAzul("lc2") + CorVermelho("lc2")) entao {
        Esperar(100)
        se (CorVerde("lc1") > CorAzul("lc1") + CorVermelho("lc1") e CorVerde("rc1") > CorAzul("rc1") + CorVermelho("rc1")) entao {
            AndarAtras()
            Esperar(400)
            se (CorVerde("rc1") + CorAzul("rc1") + CorVermelho("rc1") < 80 e CorVerde("lc1") + CorAzul("lc1") + CorVermelho("lc1") < 80) entao {
                Esperar(100)
                AndarFrente()
            }
            senao {
                CurvaCentro180()
            }
        }
        se (CorVerde("lc1") > CorAzul("lc1") + CorVermelho("lc1") ou CorVerde("lc2") > CorAzul("lc2") + CorVermelho("lc2") ou CorVerde("lc1") > CorAzul("lc1") + CorVermelho("lc1") e CorVerde("lc2") > CorAzul("lc2") + CorVermelho("lc2")) entao {
            AndarAtras()
            Esperar(400)
            Escrever("oi1")
            se (CorVerde("lc1") + CorAzul("lc1") + CorVermelho("lc1") < 80) entao {
                AndarFrente()
                Esperar(1000)
            }
            senao {
                AndarFrente()
                Esperar(1000)
                CurvaEsquerda90()
                AndarFrente()
                Esperar(300)
            }
        }  
        se (CorVerde("rc1") > CorAzul("rc1") + CorVermelho("rc1") ou CorVerde("rc2") > CorAzul("rc2") + CorVermelho("rc2") ou CorVerde("rc1") > CorAzul("rc1") + CorVermelho("rc1") e CorVerde("rc2") > CorAzul("rc2") + CorVermelho("rc2")) entao {
            AndarAtras()
            Esperar(400)
            Escrever("oi2")
            se (CorVerde("rc1") + CorAzul("rc1") + CorVermelho("rc1") < 80) entao {
                AndarFrente()
                Esperar(1000)
            }
            senao {
                AndarFrente()
                Esperar(1000)
                CurvaDireita90()
                AndarFrente()
                Esperar(300)
            }
        }
    }
}

tarefa Rampa{
    enquanto ( Ultra("UltraF1") > 2.5 e Ultra("UltraF1") < 3 e Ultra("UltraF2") > 6.2 e Ultra("UltraF2") < 7.5) farei {
        AbrirConsole()
        Escrever("Subindo Rampa")
    }
}

tarefa DesviarObstaculo2 {
    se (Ultra("UltraF1") > 0 e Ultra("UltraF1") < 1) entao {
        Escrever("Ops... um obstáculo. Devo me desviar!")
        AndarAtras()
        Esperar(1000)
        CurvaEsquerda90()
        AndarFrente()
        Esperar(2150)
        CurvaDireita90()
        AndarFrente()
        loopobstaculo = 1
        tempoInicio = CarimboMilissegundo()
        enquanto (loopobstaculo == 1) farei {
            se (Cor("rc1") == "Preto" e Cor("cc") == "Preto" e Cor("lc1") == "Preto") entao {
                loopobstaculo = 0
                Esperar(800)
                Escrever("Achei a linha novamente! Vou ter que segui-lá.")
                CurvaEsquerda90()
                tempoInicio = CarimboMilissegundo()
                AndarFrente()
            }
            se (CarimboMilissegundo() - tempoInicio > 6000 ) entao {
                Escrever("Não tem linha desse lado. Vou tentar do outro.")
                CurvaDireita90()
                AndarFrente()
                tempoInicio = CarimboMilissegundo()
                enquanto (loopobstaculo==1) farei{
                    se (Cor("rc1") == "Preto" e Cor("cc") == "Preto" e Cor("lc1") == "Preto") entao {
                        loopobstaculo = 0
                        Esperar(800)
                        Escrever("Agora sim, voltamos aos trilhos!")
                        CurvaEsquerda90()
                        tempoInicio = CarimboMilissegundo()
                        AndarFrente()
                        loopobstaculo=0
                    }
                    se (CarimboMilissegundo() - tempoInicio > 4300 ) entao {
                        Escrever("Não tem linha desse lado novamente. Vou tentar do outro agora.")
                        CurvaDireita90()
                        AndarFrente()
                        tempoInicio = CarimboMilissegundo()
                        enquanto (loopobstaculo==1) farei{
                            se (Cor("rc1") == "Preto" e Cor("cc") == "Preto" e Cor("lc1") == "Preto") entao {
                                loopobstaculo = 0
                                Esperar(800)
                                Escrever("Ufa, achei que nunca mais veria a linha novamente :)")
                                CurvaEsquerda90()
                                tempoInicio = CarimboMilissegundo()
                                AndarFrente()
                                loopobstaculo=0
                            }
                        }
                    }
                }
            }
        }
    }
}

tarefa Resgate {
    se ( CorAzul("rc1") > 67 e CorAzul("rc1") < 106 e CorAzul("cc") > 67 e CorAzul("cc") < 106 e CorAzul("lc1") > 67 e CorAzul("lc1") < 106 e CorVerde("rc1") > 75 e CorVerde("rc1") < 95 e CorVerde("cc") > 75 e CorVerde("cc") < 95 e CorVerde("lc1") > 75 e CorVerde("lc1") < 95 ) entao {
        AndarFrente()
        Esperar(1000)
        Escrever("Está na hora de resgatar as bolas!")
        resgate = 1 
        enquanto (resgate == 1) farei {
            se ( ( 5 > Ultra("UltraR") e 3 < Ultra("UltraR")) ou ( 5 > Ultra("UltraL") e 3 < Ultra("UltraL") )) entao {
                
            }
        }
    }
}

inicio
TravarMotor("frmotor", falso)
TravarMotor("flmotor", falso)
TravarMotor("brmotor", falso)
TravarMotor("blmotor", falso)
AbrirConsole()
LimparConsole()
enquanto (verdadeiro) farei {
    Rampa()
    DesviarObstaculo2()
    CurvaVerde()
    Resgate()
    PosicaoRobo() 
    MotorPID()
}

fim