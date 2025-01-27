# hello_world.rb
# A simple Ruby script for MomentumOS

puts "Welcome to MomentumOS!"

loop do
  print "MomentumOS (Ruby)> "
  input = gets.chomp

  case input
  when "help"
    puts "Available commands:"
    puts "  help  - Show this help message."
    puts "  greet - Receive a friendly greeting."
    puts "  exit  - Exit this Ruby shell."
  when "greet"
    puts "Hello, user! MomentumOS is happy to have you."
  when "exit"
    puts "Goodbye!"
    break
  else
    puts "Unknown command: #{input}"
  end
end
