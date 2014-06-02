require 'guard'
require 'guard/plugin'
require 'pry'

module ::Guard
  class Test < ::Guard::Plugin

    # Called when just `enter` is pressed
    # This method should be principally used for long action like running all specs/tests/...
    #
    # @raise [:task_has_failed] when run_all has failed
    # @return [Object] the task result
    #
    def run_all
      run_paths(['test'])
    end

    # Default behaviour on file(s) changes that the Guard plugin watches.
    # @param [Array<String>] paths the changes files or paths
    # @raise [:task_has_failed] when run_on_change has failed
    # @return [Object] the task result
    #
    def run_on_changes(paths)
      run_paths(paths)
    end

    # Called on file(s) additions that the Guard plugin watches.
    #
    # @param [Array<String>] paths the changes files or paths
    # @raise [:task_has_failed] when run_on_additions has failed
    # @return [Object] the task result
    #
    def run_on_additions(paths)
      run_paths(paths)
    end

    # Called on file(s) modifications that the Guard plugin watches.
    #
    # @param [Array<String>] paths the changes files or paths
    # @raise [:task_has_failed] when run_on_modifications has failed
    # @return [Object] the task result
    #
    def run_on_modifications(paths)
      run_paths(paths)
    end

    # Called on file(s) removals that the Guard plugin watches.
    #
    # @param [Array<String>] paths the changes files or paths
    # @raise [:task_has_failed] when run_on_removals has failed
    # @return [Object] the task result
    #
    def run_on_removals(paths)
puts "#{paths.inspect} deleted?"
    end

    def run_paths(paths)
      runnable = paths.reduce([]) do |to_run, path|
        if File.exists?(path)
          case
          when File.directory?(path)
            Dir.glob("#{path}/**/*_test.c").each do |path|
              to_run << path
            end
          when File.file?(path)
            to_run << path
          end
        end
        to_run
      end
      Kernel.system("make test")
    end

  end
end

guard 'test' do
  watch(%r{^test/(.+)_test\.c$}) do |match|
    "test/#{match[1]}_test.c"
  end

  watch(%r{^test/(.+)_test\.h$}) do |match|
    "test/#{match[1]}_test.c"
  end

  watch(%r{^src/(.+)\.c$}) do |match|
    "test/#{match[1]}_test.c"
  end

  watch(%r{^include/(.+)\.h$}) do |match|
    "test/#{match[1]}_test.c"
  end

  watch('test/main.c') do ||
    'test'
  end

  watch('Makefile') do ||
    'test'
  end
end
