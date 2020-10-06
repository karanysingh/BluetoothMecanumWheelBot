package com.example.botcontrol

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.content.Context
import android.content.Intent
import android.graphics.Color
import android.os.Bundle
import android.view.View
import android.view.ViewGroup
import android.widget.*
import android.widget.AdapterView.OnItemClickListener
import androidx.appcompat.app.AppCompatActivity
import android.widget.AdapterView
import kotlinx.android.synthetic.main.activity_main.*

var listDevices: ArrayList<String> = arrayListOf()
open class bluetooth : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_bluetooth)

        //initialisation
        val listDevicesView: ListView = findViewById<ListView>(R.id.bluetooth_listView)
        val bluetoothAdapter: BluetoothAdapter? = BluetoothAdapter.getDefaultAdapter()
        val pairedDevices: Set<BluetoothDevice>? = bluetoothAdapter?.bondedDevices


        pairedDevicesList(pairedDevices,listDevicesView)

        listDevicesView.adapter = MyCustomAdapter(this, listDevices)
    }

    private fun pairedDevicesList(pairedDevices: Set<BluetoothDevice>?,listDevicesView: ListView) {
        //fetching the list of devices connected to our device earlier
        //so the bot we are trying to connect should be known to our device in the past.
        //this is being done for the simplicity.
        if (pairedDevices != null) {
            if (pairedDevices.isNotEmpty()) {
                for (i in pairedDevices) {
                    listDevices.add("${i.name} ${i.address}")
                }
            }
        } else {
            Toast.makeText(this, "No paired Device found", Toast.LENGTH_SHORT).show()
        }

        //Onclick listener for the listview, it sends which item is clicked by the user
        //to the mainActivity (as a 'bundle').
        //activity is just an another name for the screens getting displayed to the user.
        listDevicesView.setOnItemClickListener { parent:AdapterView<*>, v:View, position:Int, id:Long ->
//             Get the device MAC address, the last 17 chars in the View
            if(position == 0){
                Toast.makeText(this,"Clicked on first item",Toast.LENGTH_SHORT).show()
            }
            val info = (v as TextView).text.toString()
            val address = info.substring(info.length - 17)



            //Make an intent to start next activity and sending data back to the mainActivity.
            //activity is just an another name for the screens getting displayed to the user.
            val i = Intent(this, MainActivity::class.java)
            println("Selected -------> $info $address")
            ////

            //Changes the activity
            //and sends a bundle containing 'EXTRA_ADDRESS' and 'INDEX' variables to the mainActivity.
            i.putExtra(
                "EXTRA_ADDRESS",
                address
            )
            i.putExtra(
                "INDEX",
                position.toString()
            )
            finish()
            startActivity(i)
            ////
        }

    }}

//The class converting the data to 'lists' being shown,
//Its getting the list of items(as variable 'items',second attr being passed to the class) and then just converts it to be shown on the actual screen.
private class MyCustomAdapter(context: Context, items: ArrayList<String>) : BaseAdapter() {
    private val mContext: Context
    private val items: ArrayList<String>

    init {
        this.mContext = context
        this.items = items
    }
    //returns the number of items in the list
    override fun getCount(): Int {
        return items.size
    }

    //returns the requested item at a position/index.
    override fun getItem(position: Int): Any {
        return "TEST STRING"
    }

    //returns the id of each item.
    override fun getItemId(position: Int): Long {
        return position.toLong()
    }

    //Gets the view from the mainactivity, where the list will be displayed.
    //'View' is analogous to the 'div' in the HTML, acts like a container to display 'something'.
    //So in our case we had earlier defined a view with name 'listDevicesView'[LINE23].
    //this piece of code fetches it and puts up a list of items there.
    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        val textView = TextView(mContext)
        textView.text = items[position]
        return textView
    }
}