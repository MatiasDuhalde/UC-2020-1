require "csv"
require_relative "classes"

def extract_sectores(data_path)
    file_path = File.join(data_path, "sectores.csv")
    sectores = []
    csv_file = CSV.read(file_path)
    headers = csv_file[0]
    csv_file.slice(1, csv_file.length).each do |line|
        h = {}
        headers.zip(line).each do |x|
            h[x[0].to_sym] = x[1]
        end
        sectores << Sector.new(**h)
    end
    sectores
end


def extract_vuelos(data_path)
    file_path = File.join(data_path, "vuelos.csv")
    vuelos = []
    csv_file = CSV.read(file_path)
    headers = csv_file[0]
    csv_file.slice(1, csv_file.length).each do |line|
        h = {}
        headers.zip(line).each do |x|
            h[x[0].to_sym] = x[1]
        end
        vuelos << Vuelo.new(**h)
    end
    vuelos
end


def extract_paises(data_path)
    file_path = File.join(data_path, "paises.csv")
    paises = []
    csv_file = CSV.read(file_path)
    headers = csv_file[0]
    csv_file.slice(1, csv_file.length).each do |line|
        h = {}
        headers.zip(line).each do |x|
            h[x[0].to_sym] = x[1]
        end
        paises << Pais.new(**h)
    end
    paises
end


def extract_habitantes(data_path, sectores)
    file_path = File.join(data_path, "habitantes.csv")
    habitantes = []
    csv_file = CSV.read(file_path)
    headers = csv_file[0]
    csv_file.slice(1, csv_file.length).each do |line|
        h = {}
        headers.zip(line).each do |x|
            h[x[0].to_sym] = x[1]
        end
        sectores.each do |sector|
            if sector.id === h[:sector].to_i
                h[:sector] = sector
                break
            end
        end
        habitantes << Habitante.new(**h)
    end
    habitantes
end


def extract_pasajeros(data_path, vuelos, paises)
    file_path = File.join(data_path, "pasajeros.csv")
    pasajeros = []
    csv_file = CSV.read(file_path)
    headers = csv_file[0]
    csv_file.slice(1, csv_file.length).each do |line|
        h = {}
        headers.zip(line).each do |x|
            h[x[0].to_sym] = x[1]
        end
        h[:vuelos] = h[:vuelos].split(":").map!(&:to_i)
        h[:paises] = h[:paises].split(":").map!(&:to_i)

        vuelos_array = []
        h[:vuelos].each do |id_vuelo|
            vuelos.each do |vuelo|
                if id_vuelo === vuelo.id
                    vuelos_array << vuelo
                    break
                end
            end
        end
        h[:vuelos] = vuelos_array

        paises_array = []
        h[:paises].each do |id_pais|
            paises.each do |pais|
                if id_pais === pais.id
                    paises_array << pais
                    break
                end
            end
        end
        h[:paises] = paises_array

        pasajeros << Pasajero.new(**h)
    end
    pasajeros
end


def extract_all(data_path)
    sectores = extract_sectores(data_path)
    vuelos = extract_vuelos(data_path)
    paises = extract_paises(data_path)
    habitantes = extract_habitantes(data_path, sectores)
    pasajeros = extract_pasajeros(data_path, vuelos, paises)
    {
        :sectores => sectores,
        :vuelos => vuelos,
        :paises => paises,
        :habitantes => habitantes,
        :pasajeros => pasajeros
    }
end


def extract_instructions(instructions_path)
    lines = []
    File.open(instructions_path, "r").each do |line|
        lines << line.chomp
    end
    lines
end