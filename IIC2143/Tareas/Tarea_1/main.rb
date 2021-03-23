require "csv"
require_relative "extract_data"
require_relative "outputter"


# Gather terminal arguments
datasets_folder = ARGV[0]
instructions_file = ARGV[1]
output_file = ARGV[2]

if not output_file
    puts("ERROR: Script requires 3 arguments (datasets_folder, instructions_file, output_file)")
    exit
end

puts("Extracting data...")
data = extract_all(datasets_folder)
puts("Extracting instructions...")
instructions = extract_instructions(instructions_file)

# NOTA: SI PARA CIERTA INSTRUCCIÓN NINGÚN DATO CUMPLE LOS CRITERIOS PARA SER
# AGREGADO AL ARCHIVO OUTPUT, DE IGUAL MANERA SE AÑADE AL ARCHIVO EL INICIO
# Y FIN DE LA CONSULTA
puts("Creating output file...")
make_blank_file(output_file)
instructions.each do |instruction|
    send(instruction, *[data, output_file])
end
puts("Terminating program...")
