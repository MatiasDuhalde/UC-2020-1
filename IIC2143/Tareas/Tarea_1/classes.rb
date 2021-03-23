# This module groups all classes modeling data objects.

class Persona
    # Clase abstracta, modela a una persona
    attr_reader :id, :nombre, :edad

    def initialize(id, nombre, edad)
        @id = id.to_i
        @nombre = nombre
        @edad = edad.to_i
    end

    def edad_de_riesgo?()
        @edad >= 65
    end
end


class Habitante < Persona
    # Modela a una persona que se encuentra en el país al comenzar el brote
    attr_reader :sector

    def initialize(id: nil, nombre: nil, edad: nil, sector: nil)
        super(id, nombre, edad)
        @sector = sector    # Sector Object
    end

    def cuarentena()
        edad_de_riesgo?() || @sector.hay_infectados
    end
end


class Pasajero < Persona
    # Modela a una persona que llega desde otro país a Chile
    attr_reader :vuelos, :paises

    def initialize(id: nil, nombre: nil, edad: nil, vuelos: nil, paises: nil)
        super(id, nombre, edad)
        @vuelos = vuelos    # List of Vuelo objects
        @paises = paises    # List of Pais objects
    end

    def min_dias_de_vuelo()
        (@vuelos.map {|x| x.dias_desde_vuelo}).min()
    end

    def get_paises_infectados()
        paises_infectados = @paises.select {|pais| pais.hay_infectados}
    end

    def get_vuelos_infectados()
        vuelos_infectados = @vuelos.select {|vuelo| vuelo.hay_infectados}
    end

    def viajo_pais_infectado?()
        return false if get_paises_infectados().empty?
        true
    end

    def viajo_con_infectado?()
        return false if get_vuelos_infectados().empty?
        true
    end

    def cuarentena()
        edad_de_riesgo?() || viajo_pais_infectado?() || \
        min_dias_de_vuelo() <= 14 || viajo_con_infectado?()
    end
end


class Sector
    # Modela un sector/región de chile
    attr_reader :id, :hay_infectados

    def initialize(id: nil, hay_infectados: nil)
        @id = id.to_i
        @hay_infectados = hay_infectados === "true"
    end
end


class Vuelo
    # Modela un vuelo (acumulación de pasajeros) internacional
    attr_reader :id, :hay_infectados, :dias_desde_vuelo

    def initialize(id: nil, hay_infectados: nil, dias_desde_vuelo: nil)
        @id = id.to_i
        @hay_infectados = hay_infectados === "true"
        @dias_desde_vuelo = dias_desde_vuelo.to_i
    end
end


class Pais
    # Modela a un país distinto a Chile
    attr_reader :id, :nombre, :hay_infectados

    def initialize(id: nil, nombre: nil, hay_infectados: nil)
        @id = id.to_i
        @nombre = nombre
        @hay_infectados = hay_infectados === "true"
    end
end
