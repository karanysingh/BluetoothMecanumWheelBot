package com.example.botcontrol

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothHeadset
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.content.Intent
import android.os.*
import android.util.Log
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*
import java.util.concurrent.Executors
import java.util.concurrent.ScheduledExecutorService
import java.util.concurrent.TimeUnit

const val REQUEST_ENABLE_BT = 4
private const val TAG = "BOT CONTROL"
val socket = null
var address: String = "00:13:EF:00:56:D9"
var btSocket: BluetoothSocket? = null
var isBtConnected = false
var bluetoothAdapter: BluetoothAdapter? = null
var deviceToTry = "1"
var pairedDevices: Set<BluetoothDevice>?= null
var device2Bt: BluetoothDevice? = null
val myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")
val looper: Looper? = null
//val btHandler = Handler(Looper looper)
open class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //question  mark represents that its nullable
        MainActivity.appContext = applicationContext

        //initialisation
        val toggleBt: Button = findViewById(R.id.toggle)
        val devicebtn: Button = findViewById(R.id.devices)
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
        var deviceName: String? = null
        var deviceHardwareAddress: String? = null
        val connectBtn: Button = findViewById(R.id.connect)

        //The Onclick listener for 'TOGGLE BLUETOOTH' button on the app.
        toggleBt.setOnClickListener {
            //if bluetooth is not supported, it prompts a message on app.
            if (bluetoothAdapter == null) {
                Toast.makeText(this,"Device doesn't support Bluetooth or no device found",Toast.LENGTH_SHORT).show()
            }

            //if bluetooth is not null (but adapter not initialised), Bluetooth is turned on and list of devices(previous connected in the past) are shown.
            if (bluetoothAdapter?.isEnabled == false) {

                //getting intent of bluetooth class(THE SCREEN WHICH SHOWS THE LIST OF BLUETOOTH DEVICES)
                val intent = Intent(this, bluetooth::class.java)
                startActivity(intent)

                //default intent provided by the Operating System, whenever we turn on the bluetooth.
                val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
                startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT)
            }

            //if bluetooth is already enabled, it will be turned off.
            if (bluetoothAdapter?.isEnabled == true) {
                bluetoothAdapter!!.disable();
            }
        };

        //The Onclick listener for 'SELECT DEVICE' button on the app.
        devicebtn.setOnClickListener {
            if (bluetoothAdapter?.isEnabled == true) {
                val intent = Intent(this, bluetooth::class.java)
                startActivity(intent)
            }
            else if (bluetoothAdapter?.isEnabled == false) {
                val Toast = Toast.makeText(this,"Enable Bluetooth first!",Toast.LENGTH_SHORT)
                Toast.show()
        }
        }

        //The Onclick listener for 'CONNECT' button on the app.
        connectBtn.setOnClickListener {
            if (bluetoothAdapter?.isEnabled == false) {
                Toast.makeText(this, "Enable Bt first!", Toast.LENGTH_SHORT).show();
            }
            if (bluetoothAdapter?.isEnabled == true) {

                //returns the list of devices connected in the past.
                pairedDevices = bluetoothAdapter?.bondedDevices

                //for each device, initialising 'deviceName' and 'deviceHardwareAddress' variables.
                pairedDevices?.forEach { device ->
                    deviceName = device.name
                    deviceHardwareAddress = device.address // MAC address
                }

                //A bundle is sent from 'bluetooth' intent that can be accessed using 'intent.extras'
                val bundle: Bundle? = intent.extras

                //default device to try from the list
                deviceToTry = "1"
                try{

                    //getStringExtra() is receiving data from other intent/window of the app
                    //The 'bluetooth' intent is sending 2 variables "INDEX" "EXTRA_ADDRESS" in the form of a 'bundle'.
                    //that we are using below.

                    //index of the device from the list of paired devices.
                    deviceToTry = intent.getStringExtra("INDEX")

                    //address of the device selected.
                    address = intent.getStringExtra("EXTRA_ADDRESS")


                    Toast.makeText(this, address, Toast.LENGTH_SHORT).show()

                }
                //Just basic exception handling so that app crashes can be prevented.
                catch (e: java.lang.Exception){
                    println(e)
                }
                }
                //Attempting to connect to the device.
                ConnectBT().execute()
            }


        //Onclick listeners for DIRECTIONAL KEYS--
        // W - Forward
        // A - Left
        // S - Backward
        // D - Right
        // L - Rotate Left
        // R - Rotate Right

        if (btSocket != null) {//Only if Bluetooth Socket is already defined the directional keys will work!!

            //character 'A' is sent to the Arduino. (which is mapped to moving left in arduino code)
            keyA.setOnClickListener{
                btSocket?.outputStream!!.write("A".toByteArray())
                Toast.makeText(this,"LEFT",Toast.LENGTH_SHORT).show()
            }

            //character 'D' is sent to the Arduino. (which is mapped to moving right in arduino code)
            keyD.setOnClickListener{
                btSocket?.outputStream!!.write("D".toByteArray())
                Toast.makeText(this,"RIGHT",Toast.LENGTH_SHORT).show()
            }

            //character 'R' is sent to the Arduino. (which is mapped to rotate right in arduino code)
            keyD2.setOnClickListener{
                btSocket?.outputStream!!.write("R".toByteArray())
            }

            //character 'D' is sent to the Arduino. (which is mapped to rotate left in arduino code)
            keyA2.setOnClickListener{
                btSocket?.outputStream!!.write("L".toByteArray())
            }

            //character 'S' is sent to the Arduino. (which is mapped to Backward in arduino code)
            keyS.setOnClickListener{
                btSocket?.outputStream!!.write("S".toByteArray())
            }

            //character 'W' is sent to the Arduino. (which is mapped to Forward in arduino code)
            keyW.setOnClickListener{
                btSocket?.outputStream!!.write("W".toByteArray())
            }
        }
    }

    //Getting the mainActivity app context to be accessed in rest of the code.
    companion object {
        lateinit var appContext: Context
        val BUNDLE_KEY = "handlerMsgBundle"
        private val TAG = javaClass.simpleName
        }
    }
//
private class recieveStream : AsyncTask<Void?, Void?, Void?>() {
    override fun doInBackground(vararg params: Void?): Void? {

        Looper.prepare()
        var mHandler = Handler(){
            val callback = Handler.Callback { message ->
                println(message)
                true
            }
            true
        }
        Looper.loop()
        var bundle = Bundle()
        var message = Message()
        bundle.putString(MainActivity.BUNDLE_KEY,"Hi")
        message.data = bundle
        mHandler.sendMessage(message)
        return null
    }
}

private class ConnectBT: AsyncTask<Void, Void, Void>() {
    private var ConnectSuccess:Boolean = true;

    //function executes before attempting to connect
    override fun onPreExecute() {

        //In this case a message prompts before each attempt.
        msg("Attempting to Connecting")

    }

    override fun doInBackground(vararg params: Void?): Void? {
        println("running in background")
        try {
            //if bluetooth socket doesn't already exists or bluetooth device is already connected.
            if( btSocket == null || isBtConnected){

                //getting 'bluetoothdevice' object from the 'address' of the device selected in the app.
                //'address' is a variable which we got from the app(after pressing 'select device' button)
                device2Bt = bluetoothAdapter?.getRemoteDevice(address);

                //attempting to connect to the device selected.
                btSocket = device2Bt?.createRfcommSocketToServiceRecord(myUUID)
                btSocket?.connect()
            }
        }catch (e:Exception){
            println("Connection Failed "+e)
            ConnectSuccess = false
    }
        return null
    }

    override fun onPostExecute(result: Void?) {

        //checking if connection was successful or not
        super.onPostExecute(result)
        if(!ConnectSuccess){
            msg("Connection Failed try again")
        }else{
            //The global variable isBtConnected is changed 'true' on successful connection
            msg("Connection Successful")
            isBtConnected = true

            //On successful connection, starting a stream to send/receive data.
            recieveStream().execute()
        }
    }

    //A method to reduce the number of Toast.makeText() calls.(REDUCES THE CODE)
    private fun msg(s:String){
        var context = MainActivity.appContext
        Toast.makeText(context, s, Toast.LENGTH_SHORT).show()
    }

    //To close bluetooth connection
    private fun Disconnect() {
        if(btSocket!=null){
            try{
                btSocket!!.close()
            }
            //Just basic exception handling so that app crashes can be prevented.
            catch (e:Exception){
                msg("Error")
            }
        }
    }
}