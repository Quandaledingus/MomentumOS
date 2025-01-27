import time
import random
import threading

class Process:
    def __init__(self, pid, name):
        self.pid = pid
        self.name = name
        self.status = "Running"
        self.start_time = time.time()
    
    def terminate(self):
        self.status = "Terminated"
        self.end_time = time.time()
        print(f"Process {self.pid} - {self.name} terminated.")

    def run(self):
        print(f"Process {self.pid} - {self.name} started.")
        # Simulating process runtime with sleep
        time.sleep(random.randint(1, 5))
        self.terminate()

class ProcessManager:
    def __init__(self):
        self.processes = []
        self.next_pid = 1

    def create_process(self, name):
        pid = self.next_pid
        process = Process(pid, name)
        self.processes.append(process)
        self.next_pid += 1
        # Simulating running the process in a separate thread
        process_thread = threading.Thread(target=process.run)
        process_thread.start()
        print(f"Process {pid} created: {name}")
    
    def terminate_process(self, pid):
        for process in self.processes:
            if process.pid == pid:
                process.terminate()
                self.processes.remove(process)
                break
        else:
            print(f"Process {pid} not found.")

    def list_processes(self):
        if not self.processes:
            print("No running processes.")
        else:
            print("Running Processes:")
            for process in self.processes:
                print(f"PID: {process.pid}, Name: {process.name}, Status: {process.status}")

def main():
    manager = ProcessManager()

    # Simulate creating processes
    manager.create_process("System Monitor")
    manager.create_process("Text Editor")
    manager.create_process("File Manager")

    time.sleep(2)  # Wait for a couple of processes to run

    manager.list_processes()

    # Terminate a process
    manager.terminate_process(2)

    time.sleep(3)  # Wait for remaining processes to finish

    manager.list_processes()

if __name__ == "__main__":
    main()
