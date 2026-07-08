import threading
import time

import serial

SERIAL_PORT = "COM3"
BAUD_RATE = 115200

sensor_data = {
    "left": 400.0,
    "mid": 400.0,
    "right": 400.0,
}

data_lock = threading.Lock()
running = True
last_packet_time = 0.0


def serial_reader_thread(ser):
    """Read telemetry packets from the ESP32."""

    global running, last_packet_time

    while running:
        try:
            line = ser.readline().decode("utf-8", errors="ignore").strip()

            if not line.startswith("S,"):
                continue

            tokens = line.split(",")
            if len(tokens) != 4:
                continue

            left = float(tokens[1])
            mid = float(tokens[2])
            right = float(tokens[3])

            with data_lock:
                sensor_data["left"] = max(0.0, left)
                sensor_data["mid"] = max(0.0, mid)
                sensor_data["right"] = max(0.0, right)
                last_packet_time = time.time()

        except ValueError:
            # Ignore malformed packets.
            continue

        except serial.SerialException:
            print("\n[ERROR] Serial connection lost.")
            running = False
            break

        except Exception as e:
            print(f"\n[ERROR] {e}")


def send_drive_command(ser, left_speed, right_speed):
    left_speed = max(-255, min(255, int(left_speed)))
    right_speed = max(-255, min(255, int(right_speed)))

    ser.write(f"M,{left_speed},{right_speed}\n".encode("utf-8"))


def main():
    global running

    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    except Exception as e:
        print(f"[ERROR] Could not open serial port: {e}")
        return

    print("[INFO] Connected.")

    reader = threading.Thread(target=serial_reader_thread, args=(ser,), daemon=True)
    reader.start()

    print("[INFO] Waiting for telemetry...")

    while running:
        with data_lock:
            if last_packet_time != 0:
                break
        time.sleep(0.05)

    print("[INFO] Robot running. Press Ctrl+C to stop.")

    CRITICAL_DISTANCE = 30.0
    CLEAR_PATH_SPEED = 150
    TURN_SPEED = 120
    TELEMETRY_TIMEOUT = 0.5

    try:
        while running:
            with data_lock:
                left = sensor_data["left"]
                mid = sensor_data["mid"]
                right = sensor_data["right"]
                age = time.time() - last_packet_time

            if age > TELEMETRY_TIMEOUT:
                print("\n[WARN] Telemetry timeout. Stopping robot.")
                send_drive_command(ser, 0, 0)
                time.sleep(0.05)
                continue

            print(
                f"Left:{left:5.1f}  Mid:{mid:5.1f}  Right:{right:5.1f}",
                end="\r",
            )

            if mid < CRITICAL_DISTANCE:
                if left > right:
                    send_drive_command(ser, -TURN_SPEED, TURN_SPEED)
                else:
                    send_drive_command(ser, TURN_SPEED, -TURN_SPEED)
                time.sleep(0.4)

            elif left < CRITICAL_DISTANCE:
                send_drive_command(
                    ser,
                    CLEAR_PATH_SPEED,
                    CLEAR_PATH_SPEED // 2,
                )

            elif right < CRITICAL_DISTANCE:
                send_drive_command(
                    ser,
                    CLEAR_PATH_SPEED // 2,
                    CLEAR_PATH_SPEED,
                )

            else:
                send_drive_command(
                    ser,
                    CLEAR_PATH_SPEED,
                    CLEAR_PATH_SPEED,
                )

            time.sleep(0.05)

    except KeyboardInterrupt:
        print("\nStopping...")

    finally:
        running = False

        try:
            send_drive_command(ser, 0, 0)
            reader.join(timeout=1)
            ser.close()
        except Exception:
            pass


if __name__ == "__main__":
    main()
