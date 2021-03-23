# This module groups all functions that output a certain block to
# the target file.

def make_blank_file(output_path)
    File.open(output_path, "w")
end


def pasajeros_en_cuarentena(data, output_path)
    pasajeros = data.instance_of?(Hash) ? data[:pasajeros] : data
    File.open(output_path, "a") do |f|
        f.puts "*** COMIENZO PASAJEROS EN CUARENTENA ***"
        pasajeros.each do |pasajero|
            if pasajero.cuarentena()
                paises_visitados = pasajero.paises.map {|pais| pais.nombre}
                f.puts "#{pasajero.nombre}: "\
                       "#{pasajero.edad}. "\
                       "#{paises_visitados.join(' - ')}. "\
                       "#{pasajero.vuelos.length}"
            end
        end
        f.puts "*** FIN PASAJEROS EN CUARENTENA ***"
    end
end


def habitantes_en_cuarentena(data, output_path)
    habitantes = data.instance_of?(Hash) ? data[:habitantes] : data
    File.open(output_path, "a") do |f|
        f.puts "*** COMIENZO HABITANTES EN CUARENTENA ***"
        habitantes.each do |habitante|
            if habitante.cuarentena()
                f.puts "#{habitante.nombre}: "\
                       "#{habitante.edad}. "\
                       "Sector #{habitante.sector.id}"
            end
        end
        f.puts "*** FIN HABITANTES EN CUARENTENA ***"
    end
end


def personas_en_cuarentena(data, output_path)
    habitantes = data.instance_of?(Hash) ? data[:habitantes] : data
    pasajeros = data.instance_of?(Hash) ? data[:pasajeros] : data
    File.open(output_path, "a") do |f|
        f.puts "*** COMIENZO PERSONAS EN CUARENTENA ***"
        habitantes.each do |habitante|
            if habitante.cuarentena()
                f.puts "#{habitante.nombre}: #{habitante.edad}. Habitante"
            end
        end
        pasajeros.each do |pasajero|
            if pasajero.cuarentena()
                f.puts "#{pasajero.nombre}: #{pasajero.edad}. Pasajero"
            end
        end
        f.puts "*** FIN PERSONAS EN CUARENTENA ***"
    end
end


def personas_en_edad_de_riesgo(data, output_path)
    habitantes = data.instance_of?(Hash) ? data[:habitantes] : data
    pasajeros = data.instance_of?(Hash) ? data[:pasajeros] : data
    File.open(output_path, "a") do |f|
        f.puts "*** COMIENZO PERSONAS EN EDAD DE RIESGO ***"
        habitantes.each do |habitante|
            if habitante.edad_de_riesgo?()
                f.puts "#{habitante.nombre}: #{habitante.edad}. Habitante"
            end
        end
        pasajeros.each do |pasajero|
            if pasajero.edad_de_riesgo?()
                f.puts "#{pasajero.nombre}: #{pasajero.edad}. Pasajero"
            end
        end
        f.puts "*** FIN PERSONAS EN EDAD DE RIESGO ***"
    end
end


def pasajeros_de_paises_infectados(data, output_path)
    pasajeros = data.instance_of?(Hash) ? data[:pasajeros] : data
    File.open(output_path, "a") do |f|
        f.puts "*** COMIENZO PASAJEROS DE PAISES INFECTADOS ***"
        pasajeros.each do |pasajero|
            nombres_paises = pasajero.get_paises_infectados().map {|pais| pais.nombre}
            if not nombres_paises.empty?
                f.puts "#{pasajero.nombre}: #{pasajero.edad}. "\
                       "#{nombres_paises.join(' - ')}"
            end
        end
        f.puts "*** FIN PASAJEROS DE PAISES INFECTADOS ***"
    end
end


def pasajeros_de_vuelos_infectados(data, output_path)
    pasajeros = data.instance_of?(Hash) ? data[:pasajeros] : data
    File.open(output_path, "a") do |f|
        f.puts "*** COMIENZO PASAJEROS DE VUELOS INFECTADOS ***"
        pasajeros.each do |pasajero|
            ids_vuelos = pasajero.get_vuelos_infectados().map {|vuelo| vuelo.id}
            if not ids_vuelos.empty?
                f.puts "#{pasajero.nombre}: #{pasajero.edad}. "\
                       "#{ids_vuelos.join(' - ')}"
            end
        end
        f.puts "*** FIN PASAJEROS DE VUELOS INFECTADOS ***"
    end
end
